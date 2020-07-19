#ifndef GAME_H
#define GAME_H

#include <server.hpp>
#include <iterator> 
#include <map> 
#include <ghost.hpp>
#include <player.hpp>
#include <algorithms.hpp>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;

/**
  * @note Variable utilizada para controlar el acceso de los threads a los mensajes.
  */
static mutex access_send;
/**
 * @note Variable utilizada para verificar si hay mensajes en la cola.
 */
static bool is_msg_to_send = false;
/**
 * @note Variable utilizada para enviar los datos por tcp.
 */
static string msg_send_tcp[20];
/**
 * @note Variable utilizada para enviar los datos por udp.
 */
static string msg_send_udp[80];

/**
 * @brief Clase game que contiene la información del juego actual del cliente.
 */
class game
{
private:
    static game *game_instance;
    /**
     * @note Variable que contiene el grid del juego y sus dimensiones.
     */
    int **grid, sizeX, sizeY;
    string str_grid;
    map<int, ghost *> ghostList;
    player *p1;
    algorithms *a1;

private:
    /**
     * Constructor de la clase game.
     */
    game()
    {
        str_grid = "";
        a1 = new algorithms();
        p1 = new player();
        sizeX = 0;
        sizeY = 0;
    }
    /**
     * Destructor de la clase game.
     */
    ~game()
    {
        deleteBitMap();
        delete (p1);
    }

public:
    /**
     * Método que obtiene la instancia del juego
     * @return - Instancia del juego
     */
    static game *getInstance();
    /**
     * Método que evita la reasignación de la instancia del juego
     * @param other - Juego creado
     */
    game(game &other) = delete;
    /**
     * Método que evita la reasignación de la instancia del juego
     */
    void operator=(const game &) = delete;

public:
    /**
     * Método que verifica si hay actualizaciones del juego en cuanto a peticiones
     */
    static void checkUpdates();
    static void moveEnemies();
    void run_game() const;
    /**
     * Método que procesa el dato ingresado para validar la petición realizada
     * @param data Petición realizada
     * @return String con el dato de la petición
     */
    string process_data(string data);
    void updateAlgorithm(string data);
    void updateLevel(string data);
    void updatePlayer(string data);
    void newBitMap(string str_bitmap);
    void deleteBitMap();

public:
    string getStrGrid() { return str_grid; }
    int ** getMatrGrid() { return grid; }
    int getSizeXMatr() { return sizeX; }
    int getSizeYMatr() { return sizeY; }
};

#endif