#ifndef SERVER_H
#define SERVER_H

#include <thread>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <mutex>
using namespace std;

class server
{
private:
    static server *server_instance;

    int clientSocket_tcp;
    int clientSocket_udp;
    sockaddr_in udpGameServer;
    string petition;

    server() {}
    ~server() {}

public:
    static server *getInstance();
    server(server &other) = delete;
    void operator=(const server &) = delete;

public:
    /**
     * @brief Inicia el servidor tipo socket.
     * 
     * El servidor esperara a que un cliente se conecte, analizará los mensajes recibidos
     * y devolvera la respuesta correspondiente.
     * 
     * @return Resultado de la operacion.
     */
    int run_server();

    /**
     * @brief Envia mensajes al cliente.
     * 
     * Este método revisa primero que hayan mensajes en la cola para ser enviados, de ser
     * así, los envía en orden de lista.
     */
    void send_msg();
};

#endif