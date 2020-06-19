#ifndef SERVER_H
#define SERVER_H

#include <iostream>


/**
 * @brief Inicia el servidor tipo socket.
 * 
 * El servidor esperara a que un cliente se conecte, analizara los mensajes recibidos
 * y devolvera la respuesta correspondiente.
 * 
 * @return Resultado de la operacion.
 */
int run_server();


#endif