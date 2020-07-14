
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

    int result = server::getInstance()->run_server();
    if (result == -1)
    {
        cout << "Error en el socket." << endl;
    }

    send.join();
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
        data.erase(0, 6);
        newBitMap(data);
        cout << "Generado el mapa de bits." << endl;
        return "";
    }
    else if (key == "player")
    {
        data.erase(0, 7);
        updatePlayer(data);
        return "";
    }
    return data;
}

void game::updatePlayer(string data)
{
    string key = "";

    int i = 0;
    while (data[i] != ',')
    {
        key += data[i];
        i++;
    }
    i++;
    if (key == "pos")
    {
        string posX = "";
        string posY = "";
        while (data[i] != ',')
        {
            posX += data[i];
            i++;
        }
        i++;
        while (i != '\n')
        {
            posY += data[i];
            i++;
        }
        p1->moveTo(stoi(posX), stoi(posY));
        if (p1->getPosX() != p1->getLastPosX() || p1->getPosY() != p1->getLastPosY())
        {
            p1->setLastPos(p1->getPosX(), p1->getPosY());
            cout << "Posición del Jugador: " << p1->getPosX() << "," << p1->getPosY() << endl;
        }
    }
    else if (key == "life")
    {
        string life = "";
        while (data[i] != '\n')
        {
            life += data[i];
            i++;
        }
        p1->setLife(stoi(life));
        cout << "Vida del Jugador: " << life << endl;
        if (p1->getLife() == 0)
        {
            cout << "Jugador Muerto: reiniciando nivel." << endl;
        }
    }
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
