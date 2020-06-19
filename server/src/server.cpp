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

int run_server(){

    /**
     * @note Crear el socket.
     */
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket == -1){
        cerr<<"No se pudo crear el socket, cerrando..."<<endl;
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
     * @note Espera una conexion.
     */
    cout<<"Esperando cliente..."<<endl;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listen_socket, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST]; //Nombre remoto del cliente.
    char service[NI_MAXSERV]; //Donde se conecta el cliente.
 
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if(getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) ==0){
        cout<<host<<" conectado en el puerto "<<service<<endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout<<host<<" conectado en el puerto " <<ntohs(client.sin_port)<<endl;
    }
    
    /**
     * @note Cierra el socket para listening.
     */
    close(listen_socket);

    char buf[4096];

    /**
     * @note Envia un mensaje inicial al cliente.
     */
    string message = "Conexión exitosa.";
    send(clientSocket, message.c_str(), message.size() + 1, 0);
    
    /**
     * @note Espera que el cliente envie un dato.
     */
    while(true){
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
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
        cout << petition;

        /**
         * @note Respuesta del servidor.
         */
        string response = "Server response.\n";
        send(clientSocket, response.c_str(), response.size() + 1, 0);
    }
    
    /**
     * @note Cierra el socket
     */
    close(clientSocket);
    
    return 0;
}