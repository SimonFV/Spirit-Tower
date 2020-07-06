
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
    thread send, moveEnemies;
    send = thread(game::checkUpdates);

    int result = server::getInstance()->run_server();
    if (result == -1)
    {
        cout << "Error al iniciar el servidor." << endl;
    }

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