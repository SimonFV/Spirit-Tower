#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <server.hpp>

using namespace std;

int max(int x, int y) { 
    if (x > y) {return x;} 
    else {return y;} 
} 


int run_server(){
    while(true){

        /////////////////SELECT///////////////////////
        fd_set master;
        FD_ZERO(&master);
        int bytesReceived;

        /////////////////CONEXION TCP/////////////////////

        /**
         * @note Crear el socket tcp listen.
         */
        int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_socket == -1){
            cerr<<"No se pudo crear el socket listen tcp, cerrando..."<<endl;
            return -1;
        }

        /**
         * @note Enlaza una ip y un numero de puerto al socket.
         */
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    
        bind(listen_socket, (sockaddr*)&hint, sizeof(hint));
        
        /**
         * @note Dice Winsock el socket es para listening.
         */
        listen(listen_socket, SOMAXCONN);
    
        /**
         * @note Espera una conexion TCP.
         */
        cout<<"Esperando cliente TCP..."<<endl;
        sockaddr_in client_tcp;
        socklen_t clientSize = sizeof(client_tcp);
    
        int clientSocket_tcp = accept(listen_socket, (sockaddr*)&client_tcp, &clientSize);
    
        char host[NI_MAXHOST]; //Nombre remoto del cliente.
        char service[NI_MAXSERV]; //Donde se conecta el cliente.
    
        memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);
    
        if(getnameinfo((sockaddr*)&client_tcp, sizeof(client_tcp), 
                        host, NI_MAXHOST, service, NI_MAXSERV, 0) ==0){
            cout<<host<<"(TCP) conectado en el puerto "<<service<<endl;
        }else{
            inet_ntop(AF_INET, &client_tcp.sin_addr, host, NI_MAXHOST);
            cout<<host<<"(TCP) conectado en el puerto " <<ntohs(client_tcp.sin_port)<<endl;
        }

        char buf[4096];

        /**
         * @note Envia un mensaje inicial al cliente.
         */
        string message = "TCP conectado";
        send(clientSocket_tcp, message.c_str(), message.size() + 1, 0);
        
        /**
         * @note Cierra el socket para listening.
         */
        close(listen_socket);


        
        /////////////////CONEXION UDP//////////////////////

        /**
         * @note Crear el socket UDP
         */
        int clientSocket_udp = socket(AF_INET, SOCK_DGRAM, 0);
        if(clientSocket_udp == -1){
            cerr<<"No se pudo crear el socket udp, cerrando..."<<endl;
            return -1;
        }
        
        /**
         * @note Enlaza una ip y un numero de puerto al socket.
         */
        sockaddr_in udpHint;
        udpHint.sin_family = AF_INET;
        udpHint.sin_port = htons(54000);
        inet_pton(AF_INET, "0.0.0.0", &udpHint.sin_addr);
    
        bind(clientSocket_udp, (sockaddr*)&hint, sizeof(hint));

        sockaddr_in client_udp;
        socklen_t clientSize_udp = sizeof(client_udp);
        char buf_udp[1024];

        ////////////////SERVIDOR UDP (JUEGO)//////////
        /**
         * @note Enlaza una ip y un numero de puerto al socket.
         */
        sockaddr_in udpGameServer;
        udpGameServer.sin_family = AF_INET;
        udpGameServer.sin_port = htons(52000);
        inet_pton(AF_INET, "0.0.0.0", &udpGameServer.sin_addr);

        /////////////////SELECT///////////////////////
        FD_SET(clientSocket_tcp, &master);
        FD_SET(clientSocket_udp, &master);

        int maxfdp1 = max(clientSocket_tcp, clientSocket_udp) + 1;

        /**
         * @note Espera que el cliente envie un dato.
         */
        while(true){
            fd_set copy = master;
            int socketCount = select(maxfdp1, &copy, nullptr, nullptr, nullptr);

            if (socketCount == -1){
                cout << "Socket error." << endl;
                break;
            }
            if (socketCount == 0){
                continue;
            }

            /**
             * @note Si el mensaje es desde TCP.
             */
            if (FD_ISSET(clientSocket_tcp, &copy)){
                memset(buf, 0, 4096);
                bytesReceived = recv(clientSocket_tcp, buf, 4096, 0);
                if (bytesReceived == -1){
                    cerr<<"Error al recibir el mensaje"<<endl;
                    break;
                }
                if (bytesReceived == 0){
                    cout<<"Cliente desconectado"<<endl;
                    break;
                }
                /**
                 * @note Peticion del cliente.
                 */
                string petition;
                petition = string(buf, 0, bytesReceived);
                //cout << "TCP: " << petition << endl;

                /**
                 * @note Respuesta del servidor.
                 */
                string response = "Resp (TCP): " + petition;
                send(clientSocket_tcp, response.c_str(), response.size() + 1, 0);

            }
            
            /**
             * @note Si el mensaje es desde UDP.
             */
            if (FD_ISSET(clientSocket_udp, &copy)){
                memset(buf_udp, 0, 1024);
                bytesReceived = recvfrom(clientSocket_udp, buf_udp, 1024, 0,
                                         (sockaddr*)&client_udp, &clientSize_udp);
                
                /**
                 * @note Peticion del cliente.
                 */
                string petition;
                petition = string(buf_udp, 0, bytesReceived);
                //cout << "UDP: " << petition << endl;

                /**
                 * @note Respuesta del servidor.
                 */
                string response = "SERVER: " + process(petition);
                sendto(clientSocket_udp, response.c_str(), response.size() + 1,
                         0, (sockaddr*)&udpGameServer, sizeof(udpGameServer));
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
    return 0;
}