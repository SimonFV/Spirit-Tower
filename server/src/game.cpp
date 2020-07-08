
#include <game.hpp>

void game::moveEnemies()
{
    while (true)
    {
        //server::getInstance()->sendMsgTcp("Moviendo enemigo...");
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
    return data;
}
