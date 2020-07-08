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

/**
 * Clase server que contiene la arquitectura del servidor del juego
 */
class server
{
private:
    /**
     * Variable que almacena la instancia del servidor
     */
    static server *server_instance;

    /**
     * Variable que contiene el socket tcp del cliente
     */
    int clientSocket_tcp;
    /**
     * Variable que contiene el soket udp del cliente
     */
    int clientSocket_udp;
    /**
     * Variable que almacena la dirección del socket
     */
    sockaddr_in udpGameServer;
    /**
     * Varriable que contiene el tipo de petición hecha por el usuario
     */
    string petition;

    /**
     * Constructor de la clase server
     */
    server() {}
    /**
     * Destructor de la clase server
     */
    ~server() {}

public:
    /**
     * Método que obtiene la instancia del servidor
     * @return - Instancia del servidor
     */
    static server *getInstance();
    /**
     * Método que evita la reasignación de la instancia del servidor
     * @param other - Servidor creado
     */
    server(server &other) = delete;
    /**
     * Método que evita la reasignación de la instancia del servidor
     */
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
    void sendMsgTcp(string msg);
    void sendMsgUdp(string msg);
};

#endif