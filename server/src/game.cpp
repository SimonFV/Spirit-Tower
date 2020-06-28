
#include <game.hpp>

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
    thread send;
    send = thread(game::checkUpdates);

    server::getInstance()->run_server();

    send.join();
}

string game::process_data(string data)
{
    int i = 0;
    if (data[i] = 'p')
    {
        return data.erase(0, 1);
    }
    return "";
}