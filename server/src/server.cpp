
#include <game.hpp>

using namespace std;

server *server::server_instance = nullptr;

server *server::getInstance()
{
    if (server_instance == nullptr)
    {
        server_instance = new server();
    }
    return server_instance;
}

int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int server::run_server()
{
    while (true)
    {
        /////////////////SELECT///////////////////////
        FD_ZERO(&master);

        /////////////////CONEXION TCP/////////////////////

        /**
         * @note Crear el socket tcp listen.
         */
        int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_socket == -1)
        {
            spdlog::error("No se pudo crear el socket listen tcp, cerrando...");
            return -1;
        }

        /**
         * @note Enlaza una ip y un numero de puerto al socket.
         */
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

        bind(listen_socket, (sockaddr *)&hint, sizeof(hint));

        /**
         * @note Dice Winsock el socket es para listening.
         */
        listen(listen_socket, SOMAXCONN);

        /**
         * @note Espera una conexion TCP.
         */
        spdlog::info("Esperando cliente...");
        sockaddr_in client_tcp;
        socklen_t clientSize = sizeof(client_tcp);

        clientSocket_tcp = accept(listen_socket, (sockaddr *)&client_tcp, &clientSize);

        char host[NI_MAXHOST];    //Nombre remoto del cliente.
        char service[NI_MAXSERV]; //Donde se conecta el cliente.

        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if (getnameinfo((sockaddr *)&client_tcp, sizeof(client_tcp),
                        host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
        {
            spdlog::info("{}[TCP] conectado en el puerto {}.", host, service);
        }
        else
        {
            inet_ntop(AF_INET, &client_tcp.sin_addr, host, NI_MAXHOST);
            spdlog::info("{}[TCP] conectado en el puerto {}.", host, ntohs(client_tcp.sin_port));
        }

        /**
         * @note Cierra el socket para listening.
         */
        close(listen_socket);

        /////////////////CONEXION UDP//////////////////////

        /**
         * @note Crear el socket UDP
         */
        clientSocket_udp = socket(AF_INET, SOCK_DGRAM, 0);
        if (clientSocket_udp == -1)
        {
            spdlog::error("No se pudo crear el socket udp, cerrando...");
            return -1;
        }

        /**
         * @note Enlaza una ip y un numero de puerto al socket.
         */
        sockaddr_in udpHint;
        udpHint.sin_family = AF_INET;
        udpHint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &udpHint.sin_addr);

        bind(clientSocket_udp, (sockaddr *)&udpHint, sizeof(udpHint));

        clientSize_udp = sizeof(client_udp);

        ////////////////DIRECCION SERVIDOR UDP (JUEGO)//////////
        /**
         * @note Enlaza una ip y un numero de puerto.
         */
        udpGameServer.sin_family = AF_INET;
        udpGameServer.sin_port = htons(52000);
        inet_pton(AF_INET, "0.0.0.0", &udpGameServer.sin_addr);

        bind(clientSocket_udp, (sockaddr *)&udpGameServer, sizeof(udpGameServer));

        /////////////////SELECT///////////////////////
        FD_SET(clientSocket_tcp, &master);
        FD_SET(clientSocket_udp, &master);

        /**
         * @note Espera que el cliente envie un dato.
         */
        while (true)
        {
            if (receive_msg() == -1)
            {
                break;
            }
        }

        FD_CLR(clientSocket_tcp, &master);
        FD_CLR(clientSocket_udp, &master);

        /**
         * @note Cierra el socket
         */
        close(clientSocket_tcp);
        close(clientSocket_udp);
    }
}

int server::receive_msg()
{
    maxfdp1 = max(clientSocket_tcp, clientSocket_udp) + 1;

    fd_set copy = master;
    socketCount = select(maxfdp1, &copy, nullptr, nullptr, nullptr);

    if (socketCount == -1)
    {
        spdlog::error("Error de conexión. Reiniciando...");
        return -1;
    }

    /**
     * @note Si el mensaje es desde TCP.
     */
    if (FD_ISSET(clientSocket_tcp, &copy))
    {
        memset(buf, 0, 4096);
        bytesReceived = recv(clientSocket_tcp, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            spdlog::error("Error al recibir el mensaje.");
            return -1;
        }
        if (bytesReceived == 0)
        {
            spdlog::info("Cliente desconectado.");
            return -1;
        }
        /**
                 * @note Peticion del cliente.
                 */
        petition = string(buf, 0, bytesReceived);
    }

    /**
             * @note Si el mensaje es desde UDP.
             */
    if (FD_ISSET(clientSocket_udp, &copy))
    {
        memset(buf_udp, 0, 1024);
        bytesReceived = recvfrom(clientSocket_udp, buf_udp, 1024, 0,
                                 (sockaddr *)&client_udp, &clientSize_udp);
        /**
         * @note Peticion del cliente.
         */
        petition = string(buf_udp, 0, bytesReceived);
    }

    /**
     * @note Procesa la petición del cliente y devuelve una respuesta si es necesario.
     */
    sendMsgTcp(game::getInstance()->process_data(petition));
}

void server::send_msg()
{
    lock_guard<mutex> lock(access_send);
    if (is_msg_to_send)
    {
        for (int i = 0; msg_send_udp[i] != "" &&
                        i < sizeof(msg_send_udp) / sizeof(msg_send_udp[0]) - 1;
             i++)
        {
            sendto(clientSocket_udp, msg_send_udp[i].c_str(), msg_send_udp[i].size() + 1,
                   0, (sockaddr *)&udpGameServer, sizeof(udpGameServer));
            msg_send_udp[i] = "";
        }

        for (int i = 0; msg_send_tcp[i] != "" &&
                        i < sizeof(msg_send_tcp) / sizeof(msg_send_tcp[0]) - 1;
             i++)
        {
            send(clientSocket_tcp, msg_send_tcp[i].c_str(), msg_send_tcp[i].size() + 1, 0);
            msg_send_tcp[i] = "";
        }
    }
    is_msg_to_send = false;
}

void server::sendMsgTcp(string msg) const
{
    lock_guard<mutex> lock(access_send);
    if (msg != "")
    {
        int i = 0;
        while (msg_send_tcp[i] != "" && i < sizeof(msg_send_tcp) / sizeof(msg_send_tcp[0]) - 1)
        {
            i++;
        }
        msg_send_tcp[i] = msg;
        is_msg_to_send = true;
    }
}

void server::sendMsgUdp(string msg) const
{
    lock_guard<mutex> lock(access_send);
    if (msg != "")
    {
        int i = 0;
        while (msg_send_udp[i] != "" && i < sizeof(msg_send_udp) / sizeof(msg_send_udp[0]) - 1)
        {
            i++;
        }
        msg_send_udp[i] = msg;
        is_msg_to_send = true;
    }
}