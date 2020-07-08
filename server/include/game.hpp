#ifndef GAME_H
#define GAME_H

#include <server.hpp>
#include <unordered_map>
#include <ghost.hpp>
#include <player.hpp>

using namespace std;

/**
 * @note Mensajes utilizados por los distintos threads y las llaves para accesarlos.
 */
/**
  * Variable utilizada para verificar si se envían correctamente los datos
  */
static mutex access_send;
/**
 * Variable utilizada para verificar si se reciben correctamente los datos
 */
static mutex access_recv;
/**
 * Variable utilizada para verificar si el mensaje está en espera para enviarse
 */
static bool is_msg_to_send = false;
/**
 * Variable utilizada para verificar si se recibieron correctamente los datos vía tcp
 */
static string msg_recv_tcp = "";
/**
 * Variable utilizada para verificar si se recibieron correctamente los datos vía udp
 */
static string msg_recv_udp = "";
/**
 * Variable utilizada para enviar los datos vía tcp
 */
static string msg_send_tcp[20];
/**
 * Variable utilizada para enviar los datos vía udp
 */
static string msg_send_udp[80];

/**
 * Clase game creada como molde para procesar el juego
 */
class game
{
private:
    /**
     * Variable que contiene el grid del juego
     */
    int grid[200][200];
    unordered_map<int, ghost *> list;
    player p1;

public:
    /**
     * Constructor de la clase game
     */
    game() {}
    /**
     * Destructor de la clase game
     */
    ~game() {}

public:
    /**
     * Método que verifica si hay actualizaciones del juego en cuanto a peticiones
     */
    static void checkUpdates();
    static void moveEnemies();
    void run_game();
    /**
     * Método que procesa el dato ingresado para validar la petición realizada
     * @param data Petición realizada
     * @return String con el dato de la petición
     */
    static string process_data(string data);
};

#endif