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
    }else if (key == "espectros")
    {
        data.erase(0, 10);
        updateEspectros(data);
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
            if(data[i] != '.' && parada == false){
                posX += data[i];
            }else{
                parada = true;
            }
            i++;
        }
        i++;
        parada = false;
        while (data[i] != '\n')
        {
            if(data[i] != '.' && parada == false){
                posY += data[i];
            }else{
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
    // Enviar ruta breadcrumbing
    //server::getInstance()->sendMsgTcp(key+","+
    //    to_string(p1->getPosX())+"-"+to_string(p1->getPosY()));

    if (key == "0")
    {   
        // Espectro "key" -> enviar breadcrumbing
        string msj_ruta = key+","+"9"+"_"+"18"+"/"+"9"+"_"+"12"+"/"+"9"+"_"+"6"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        // A los otros espectros -> enviar aStar
        // ---- Ejecutar A Star (y_inicial, x_inicial, y_final, x_final)

        // Espectro 1
        spdlog::info(ghostList[1]->getPosX());
        spdlog::info(ghostList[1]->getPosY());
        spdlog::info(p1->getPosX());
        spdlog::info(p1->getPosY());
        string aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[1]->getPosY(), 
                                                        ghostList[1]->getPosX()),
                                                            make_pair(p1->getPosY(),
                                                                p1->getPosX()));
        if(aStar_1 == "Source is invalid"){
            aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[1]->getPosY() + 1, 
                                                        ghostList[1]->getPosX()),
                                                            make_pair(p1->getPosY(),
                                                                p1->getPosX()));
            msj_ruta = "1," + aStar_1;
            server::getInstance()->sendMsgUdp(msj_ruta);
        }else if(aStar_1 == "Destination is invalid"){

        }else if(aStar_1 == "Source or the destination is blocked"){
            aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[1]->getPosY() + 1, 
                                                        ghostList[1]->getPosX()),
                                                            make_pair(p1->getPosY(),
                                                                p1->getPosX()));
            if(aStar_1 == "Source or the destination is blocked"){
                aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[1]->getPosY() - 1, 
                                                        ghostList[1]->getPosX()),
                                                            make_pair(p1->getPosY(),
                                                                p1->getPosX()));
                if(aStar_1 == "Source or the destination is blocked"){
                    aStar_1 = a1->algoritmo_aStar(make_pair(ghostList[1]->getPosY() + 1, 
                                                            ghostList[1]->getPosX() - 1),
                                                                make_pair(p1->getPosY(),
                                                                    p1->getPosX()));
                    msj_ruta = "1," + aStar_1;
                    server::getInstance()->sendMsgUdp(msj_ruta);
                }else{
                        msj_ruta = "1," + aStar_1;
                        server::getInstance()->sendMsgUdp(msj_ruta);
                }
            }else{
                msj_ruta = "1," + aStar_1;
                server::getInstance()->sendMsgUdp(msj_ruta);
            }


        }else if(aStar_1 == "We are already at the destination"){

        }else if(aStar_1 == "No encontrado"){

        }else{
            msj_ruta = "1," + aStar_1;
            server::getInstance()->sendMsgUdp(msj_ruta);
        }


        // Espectro 2
        //key = "2";
        //msj_ruta = key+","+"5"+"_"+"0"+"/"+"5"+"_"+"7"+"/"+"5"+"_"+"12"+"/";
        //server::getInstance()->sendMsgUdp(msj_ruta);


         
    }else if (key == "1")
    {
        string msj_ruta = key+","+"-5"+"_"+"0"+"/"+"-5"+"_"+"7"+"/"+"-5"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        // A los otros espectros -> enviar aStar
        key = "0";
        msj_ruta = key+","+"0"+"_"+"0"+"/"+"0"+"_"+"7"+"/"+"0"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        key = "2";
        msj_ruta = key+","+"5"+"_"+"0"+"/"+"5"+"_"+"7"+"/"+"5"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);


    }else if (key == "2")
    {
        string msj_ruta = key+","+"-5"+"_"+"0"+"/"+"-5"+"_"+"7"+"/"+"-5"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        // A los otros espectros -> enviar aStar
        key = "0";
        msj_ruta = key+","+"0"+"_"+"0"+"/"+"0"+"_"+"7"+"/"+"0"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);

        key = "1";
        msj_ruta = key+","+"5"+"_"+"0"+"/"+"5"+"_"+"7"+"/"+"5"+"_"+"12"+"/";
        server::getInstance()->sendMsgUdp(msj_ruta);
    }

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
