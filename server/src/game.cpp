
#include <game.hpp>

void game::moveEnemies()
{
    while (true)
    {

        sendMsgTcp("Moviendo enemigo...");
        usleep(1000000);
    }
}

void game::checkUpdates()
{
    while (true)
    {
        server::getInstance()->send_msg();
        usleep(1000);
    }
}

void game::run_game()
{
    thread send, movEnem;
    send = thread(game::checkUpdates);
    movEnem = thread(game::moveEnemies);

    int result = server::getInstance()->run_server();
    if (result == -1)
    {
        cout << "Error el socket." << endl;
    }

    send.join();
    movEnem.join();
}

string game::process_data(string data)
{
}

void game::sendMsgTcp(string msg)
{
    access_send.lock();
    int i = 0;
    while (msg_send_tcp[i] != "" && i < sizeof(msg_send_tcp) / sizeof(msg_send_tcp[0]) - 1)
    {
        i++;
    }
    msg_send_tcp[i] = msg;
    is_msg_to_send = true;
    access_send.unlock();
}

void game::sendMsgUdp(string msg)
{
    access_send.lock();
    int i = 0;
    while (msg_send_udp[i] != "" && i < sizeof(msg_send_udp) / sizeof(msg_send_udp[0]) - 1)
    {
        i++;
    }
    msg_send_udp[i] = msg;
    is_msg_to_send = true;
    access_send.unlock();
}