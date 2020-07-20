#include <algorithms.hpp>
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

[[noreturn]] void game::checkUpdates()
{
    while (true)
    {
        server::getInstance()->send_msg();
        nanosleep((const struct timespec[]){{0, 1000000L}}, NULL);
    }
}

void game::run_game() const
{

    thread send;
    send = thread(game::checkUpdates);

    int result = server::getInstance()->run_server();
    if (result == -1)
    {
        spdlog::error("Error en el servidor.");
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
        spdlog::info(str_grid);
        return "";
    }
    else if (key == "player")
    {
        data.erase(0, 7);
        updatePlayer(data);
        return "";
    }
    else if (key == "level")
    {
        data.erase(0, 6);
        updateLevel(data);
        return "";
    }
    else if (key == "algorithm")
    {
        data.erase(0, 10);
        updateAlgorithm(data);
        return "";
    }
    spdlog::info("Client: {}", data);
    return data;
}

void game::updateAlgorithm(string data)
{
    string key = "";

    int i = 0;
    while (data[i] != ',')
    {
        key += data[i];
        i++;
    }
    i++;

    if (key == "aStar")
    {

        string ID_ghost = "";
        while (data[i] != ',')
        {
            ID_ghost += data[i];
            i++;
        }
        i++;

        // Enviar algoritmo
        // spdlog::info(a1->algoritmo_aStar(make_pair(5, 8), make_pair(11, 23)));
        // ---- Ejecutar A Star (y_inicial, x_inicial, y_final, x_final)
        spdlog::info(a1->algoritmo_aStar(make_pair(p1->getPosY(), p1->getPosX()),
                                         make_pair(ghostList[stoi(ID_ghost)]->getPosY(),
                                                   ghostList[stoi(ID_ghost)]->getPosX())));
    }
    else if (key == "bresenham")
    {

        string ID_ghost = "";
        while (data[i] != ',')
        {
            ID_ghost += data[i];
            i++;
        }
        i++;

        // ---- Ejecutar Bresenham (x_inicial, y_inicial, x_final, y_final)
        //spdlog::info(a1->algoritmo_bresenham(1,1,8,5));
        spdlog::info(a1->algoritmo_bresenham(p1->getPosX(), p1->getPosY(),
                                             ghostList[stoi(ID_ghost)]->getPosX(),
                                             ghostList[stoi(ID_ghost)]->getPosY()));
    }
    else if (key == "backtracking")
    {

        string ID_ghost = "";
        while (data[i] != ',')
        {
            ID_ghost += data[i];
            i++;
        }
        i++;

        // ---- Ejecutar Backtracking (y_inicial, x_inicial, x_final, y_final)
        /*vector<vector<int>> solution;  
        if(a1->algoritmo_backtracking(5, 8, 11, 5, mapa, solution)){
            spdlog::info(a1->ruta_backtracking());
        }else{
            spdlog::error("No hay solucion");
        }*/
    }
}

void game::updateLevel(string data)
{
    string key = "";

    int i = 0;
    while (data[i] != ',')
    {
        key += data[i];
        i++;
    }
    i++;

    if (key == "1")
    {

        spdlog::info("Nivel 1");

        // Crea los espectros
        ghostList[1] = new grayGhost(1);
        ghostList[2] = new grayGhost(2);
        ghostList[3] = new grayGhost(3);

        // Inicializa las posiciones

        // Inicializa la poblacion inicial
        a1->setPopulation(a1->crearPoblacion());

        // Asigna los atributos a la poblacion inicial
        int n_population = 0;
        for (auto x : ghostList)
        {
            x.second->setSpeedPatrol(a1->getPopulation()[n_population][0]);
            x.second->setSpeedPersec(a1->getPopulation()[n_population][1]);
            x.second->setVisionRange(a1->getPopulation()[n_population][2]);
            n_population += 1;
        }

        // Grid del mapa
        //spdlog::info(str_grid);
    }
    else if (key == "2")
    {
        spdlog::info("Nivel 2");

        a1->setPopulation(a1->evolucionar(a1->getPopulation(), 4, 4));
        spdlog::info("Poblacion Evolucionada");
    }
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
        while (data[i] != '\n')
        {
            posY += data[i];
            i++;
        }
        p1->moveTo(stoi(posX), stoi(posY));
        if (p1->getPosX() != p1->getLastPosX() || p1->getPosY() != p1->getLastPosY())
        {
            p1->setLastPos(p1->getPosX(), p1->getPosY());
            spdlog::info("Posición del Jugador: [ x = {}, y = {} ]", p1->getPosX(), p1->getPosY());
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
        spdlog::info("Vida del Jugador: {}", life);
        if (p1->getLife() == 0)
        {
            spdlog::info("Jugador Muerto: reiniciando nivel.");
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
    for (int i = 0; i < str_bitmap.length(); i++)
    {
        if (str_bitmap[i] == '\n')
        {
            sizeY++;
        }
    }

    grid = new int *[sizeX - 1];
    for (int i = 0; i < sizeX - 1; i++)
    {
        grid[i] = new int[sizeY];
    }

    for (int j = 1; j <= sizeY; j++)
    {
        for (int i = 1; i < sizeX; i++)
        {
            grid[i - 1][j - 1] = str_bitmap[i + ((j - 1) * sizeX)] - '0';
        }
    }

    /**
     * @note genera un string con el mapa de bits para representarlo en consola.
     */

    str_grid = "Generado el mapa de bits del nivel:\n";
    for (int j = 0; j < sizeY; j++)
    {
        for (int i = 0; i < sizeX - 1; i++)
        {
            str_grid += to_string(grid[i][j]) + " ";
        }
        str_grid += "\n";
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
