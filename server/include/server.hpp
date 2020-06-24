#ifndef SERVER_H
#define SERVER_H

#include <iostream>
using namespace std;

/**
 * @brief Inicia el servidor tipo socket.
 * 
 * El servidor esperara a que un cliente se conecte, analizara los mensajes recibidos
 * y devolvera la respuesta correspondiente.
 * 
 * @return Resultado de la operacion.
 */
int run_server();

/**
 * @brief Procesa la petición del cliente.
 * 
 * Aplica los algoritmos necesarios a la información enviada por el cliente y devuelve
 * la respuesta correspondiente.
 * 
 * @return Mensaje para el cliente.
 */
string process(string data);

#endif