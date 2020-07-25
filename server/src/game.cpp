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

void game::checkUpdates()
{
    while (true)
    {
        try
        {
            server::getInstance()->send_msg();
            nanosleep((const struct timespec[]){{0, 1000000L}}, NULL);
        }
        catch (exception)
        {
            break;
        }
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
    else if (key == "dentroVision")
    {
        data.erase(0, 13);
        updateAlgorithm(data);
        return "";
    }
    else if (key == "espectros")
    {
        data.erase(0, 10);
        updateEspectros(data);
        return "";
    }
    else if (key == "cofrenada")
    {
        spdlog::info("Cofre abierto: Vacio.");
        return "";
    }
    else if (key == "cofrellave")
    {
        spdlog::info("Cofre abierto: Llave adquirida.");
        ;
        return "";
    }
    else if (key == "weapon")
    {
        data.erase(0, 7);
        updateWeapon(data);
        return "";
    }
    else if (key == "mele")
    {
        data.erase(0, 5);
        updateMele(data);
        return "";
    }
    spdlog::info("Client: {}", data);
    return data;
}

void game::updateEspectros(string data)
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

        key = "";

        while (data[i] != ',')
        {
            key += data[i];
            i++;
        }
        i++;

        string posX = "";
        string posY = "";
        bool parada = false;
        while (data[i] != ',')
        {
            if (data[i] != '.' && parada == false)
            {
                posX += data[i];
            }
            else
            {
                parada = true;
            }
            i++;
        }
        i++;
        parada = false;
        while (data[i] != '\n')
        {
            if (data[i] != '.' && parada == false)
            {
                posY += data[i];
            }
            else
            {
                parada = true;
            }
            i++;
        }

        ghostList[stoi(key)]->moveGhostTo(stoi(posX), stoi(posY));
        spdlog::info("Posición del Espectro: [ x = {}, y = {} ]",
                     ghostList[stoi(key)]->getPosX(),
                     ghostList[stoi(key)]->getPosY());
    }
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

    spdlog::info("El espectro " + key + " detecto al jugador");

    //if (key == "0")
    //{
    string msj_ruta;

    // A los otros espectros -> enviar aStar
    // ---- Ejecutar A Star (y_inicial, x_inicial, y_final, x_final)
    int mover_a;
    for (int i = 0; i < 3; i++)
    {

        mover_a = i;
        spdlog::info(ghostList[mover_a]->getPosX());
        spdlog::info(ghostList[mover_a]->getPosY());
        spdlog::info(p1->getPosX());
        spdlog::info(p1->getPosY());
        string aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[mover_a]->getPosY(),
                                                       ghostList[mover_a]->getPosX()),
                                             make_pair(p1->getPosY(),
                                                       p1->getPosX()));
        if (aStar_1 == "Source is invalid")
        {
            aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[mover_a]->getPosY() + 1,
                                                    ghostList[mover_a]->getPosX()),
                                          make_pair(p1->getPosY(),
                                                    p1->getPosX()));
            msj_ruta = to_string(mover_a) + "," + aStar_1;
            server::getInstance()->sendMsgUdp(msj_ruta);
        }
        else if (aStar_1 == "Destination is invalid")
        {
            aStar_1 = "Error";
        }
        else if (aStar_1 == "Source or the destination is blocked")
        {
            aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[mover_a]->getPosY() - 1,
                                                    ghostList[mover_a]->getPosX()),
                                          make_pair(p1->getPosY(),
                                                    p1->getPosX()));
            if (aStar_1 == "Source or the destination is blocked")
            {
                aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[mover_a]->getPosY() + 1,
                                                        ghostList[mover_a]->getPosX() - 1),
                                              make_pair(p1->getPosY(),
                                                        p1->getPosX()));
                msj_ruta = to_string(mover_a) + "," + aStar_1;
                server::getInstance()->sendMsgUdp(msj_ruta);
            }
            else
            {
                msj_ruta = to_string(mover_a) + "," + aStar_1;
                server::getInstance()->sendMsgUdp(msj_ruta);
            }
        }
        else
        {
            msj_ruta = to_string(mover_a) + "," + aStar_1;
            server::getInstance()->sendMsgUdp(msj_ruta);
        }
    }

    //}
    /*else if (key == "1")
    {
        string msj_ruta = key + "," + "-5" + "_" + "0" + "/" + "-5" + "_" + "7" + "/" + "-5" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        // A los otros espectros -> enviar aStar
        key = "0";
        msj_ruta = key + "," + "0" + "_" + "0" + "/" + "0" + "_" + "7" + "/" + "0" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        key = "2";
        msj_ruta = key + "," + "5" + "_" + "0" + "/" + "5" + "_" + "7" + "/" + "5" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);
    }
    else if (key == "2")
    {
        string msj_ruta = key + "," + "-5" + "_" + "0" + "/" + "-5" + "_" + "7" + "/" + "-5" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        // A los otros espectros -> enviar aStar
        key = "0";
        msj_ruta = key + "," + "0" + "_" + "0" + "/" + "0" + "_" + "7" + "/" + "0" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        key = "1";
        msj_ruta = key + "," + "5" + "_" + "0" + "/" + "5" + "_" + "7" + "/" + "5" + "_" + "12" + "/";
        server::getInstance()->sendMsgUdp(msj_ruta);
    }*/

    /*
        // ---- Ejecutar Bresenham (x_inicial, y_inicial, x_final, y_final)
        //spdlog::info(a1->algoritmo_bresenham(1,1,8,5));
        spdlog::info(a1->algoritmo_bresenham(p1->getPosX(), p1->getPosY(),
                                             ghostList[stoi(ID_ghost)]->getPosX(),
                                             ghostList[stoi(ID_ghost)]->getPosY()));
    
    */

    /*
        // ---- Ejecutar Backtracking (y_inicial, x_inicial, x_final, y_final)
        vector<vector<int>> solution;  
        if(a1->algoritmo_backtracking(5, 8, 11, 5, mapa, solution)){
            spdlog::info(a1->ruta_backtracking());
        }else{
            spdlog::error("No hay solucion");
        }
    */
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
        ghostList[0] = new grayGhost(0);
        ghostList[1] = new grayGhost(1);
        ghostList[2] = new grayGhost(2);

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
    }
    else if (key == "2")
    {
        spdlog::info("Nivel 2");

        // Vaciar hashmap del nivel 1
        ghostList.clear();
        // Eliminar las instancias de los espectros del nivel 1

        // Crea los nuevos espectros
        ghostList[0] = new redGhost(0);
        ghostList[1] = new redGhost(1);
        ghostList[2] = new redGhost(2);

        a1->setPopulation(a1->evolucionar(a1->getPopulation(), 4, 4));
        spdlog::info("Poblacion Evolucionada");
    }
    else if (key == "3")
    {
        spdlog::info("Nivel 3");

        // Vaciar hashmap del nivel 1
        ghostList.clear();
        // Eliminar las instancias de los espectros del nivel 1

        // Crea los nuevos espectros
        ghostList[0] = new blueGhost(0);
        ghostList[1] = new blueGhost(1);
        ghostList[2] = new blueGhost(2);
        ghostList[3] = new blueGhost(3);
        ghostList[4] = new blueGhost(4);
        ghostList[5] = new blueGhost(5);

        a1->setPopulation(a1->evolucionar(a1->getPopulation(), 5, 5));
        spdlog::info("Poblacion Evolucionada");
    }
    else if (key == "4")
    {
        spdlog::info("Nivel 4");

        // Vaciar hashmap del nivel 1
        ghostList.clear();
        // Eliminar las instancias de los espectros del nivel 1

        // Crea los nuevos espectros
        ghostList[0] = new grayGhost(0);
        ghostList[1] = new redGhost(1);
        ghostList[2] = new blueGhost(2);

        a1->setPopulation(a1->evolucionar(a1->getPopulation(), 6, 6));
        spdlog::info("Poblacion Evolucionada");
    }
    else if (key == "5")
    {
        spdlog::info("Nivel 5");

        // Vaciar hashmap del nivel 1
        ghostList.clear();
        // Eliminar las instancias de los espectros del nivel 1

        spdlog::info("Creando el jefe final.");
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

void game::updateWeapon(string data)
{
    if (data == "0")
    {
        spdlog::info("Sin armas.");
    }
    else if (data == "1")
    {
        spdlog::info("Utilizando la espada.");
    }
    else
    {
        spdlog::info("Utilizando el escudo.");
    }
}

void game::updateMele(string data)
{
    if (data == "ghost")
    {
        spdlog::info("Ataque enemigo: Jugador dañado.");
    }
    else if (data == "player")
    {
        spdlog::info("Espectro eliminado.");
    }
    else if (data == "fuego")
    {
        spdlog::info("Trampa de fuego: Jugador dañado.");
    }
    else if (data == "picos")
    {
        spdlog::info("Trampa de picos: Jugador dañado.");
    }
}