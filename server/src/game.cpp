
#include <game.hpp>

using namespace std;

game *game::game_instance = nullptr;

game *game::getInstance()
{
    if (game_instance == nullptr)
    {
        game_instance = new game();
    }
    return game_instance;
}

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
        cout << "Error en el socket." << endl;
    }

    send.join();
    movEnem.join();
}

string game::process_data(string data)
{
    string key = "";
    for (int i = 0; i < data.length() && data[i] != ','; i++)
    {
        key += data[i];
    }

    if (key == "bitmap")
    {
        if (grid != nullptr)
        {
            deleteBitMap();
        }
        string new_map = data.erase(0, 6);
        newBitMap(new_map);
        cout << "Generado el mapa de bits." << endl;
        for (int j = 0; j < sizeY; j++)
        {
            for (int i = 0; i < sizeX - 1; i++)
            {
                cout << grid[i][j];
            }
            cout << endl;
        }
        return "";
    }
    return data;
}

void game::newBitMap(string str_bitmap)
{
    sizeX = 0;
    while (str_bitmap[sizeX] != '\n')
    {
        sizeX++;
    }
    sizeY = 0;
    while (sizeX + sizeY < str_bitmap.length())
    {
        sizeY++;
    }

    grid = new int *[sizeX - 1];
    for (int i = 0; i < sizeX - 1; i++)
    {
        grid[i] = new int[sizeY];
    }

    for (int j = 0; j < sizeY; j++)
    {
        for (int i = 1; i < sizeX; i++)
        {
            grid[i - 1][j] = str_bitmap[i + j] - '0';
        }
    }
}

void game::deleteBitMap()
{
    for (int i = 0; i < sizeX - 1; i++)
    {
        delete[] grid[i];
    }
    if (sizeY > 0)
    {
        delete[] grid;
    }
}
