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
static mutex access_send;
static mutex access_recv;
static bool is_msg_to_send = false;
static string msg_recv_tcp = "";
static string msg_recv_udp = "";
static string msg_send_tcp[20];
static string msg_send_udp[80];

class game
{
private:
    int grid[200][200];

public:
    game() {}
    ~game() {}

public:
    static void checkUpdates();
    void run_game();
    string process_data(string data);
};

#endif