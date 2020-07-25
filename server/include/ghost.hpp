#ifndef GHOST_H
#define GHOST_H
/**
 * @brief Clase ghost que representa a la base de los enemigos del juego
 */
class ghost
{
private:
    int ID;
    int ruta[10];
    /**
     * @note Variable que almacena la posición del enemigo
     */
    int position[2];
    /**
     * @note Variable que contiene la velocidad de movimiento del enemigo
     */
    int speedPatrol;
    int speedPersec;
    int visionRange;

public:
    /**
     * Constructor de la clase ghost
     */
    ghost() {}
    /**
     * Destructor de la clase ghost
     */
    ~ghost() {}
    friend class grayGhost;
    friend class redGhost;
    friend class blueGhost;

public:
    void setSpeedPatrol(int speedPatrol_nuevo)
    {
        speedPatrol = speedPatrol_nuevo;
    }

    void setSpeedPersec(int speedPersec_nuevo)
    {
        speedPersec = speedPersec_nuevo;
    }

    void setVisionRange(int visionRange_nuevo)
    {
        visionRange = visionRange_nuevo;
    }

    void moveGhostTo(int x, int y)
    {
        position[0] = x;
        position[1] = y;
    }

public:
    int getSpeedPatrol() { return speedPatrol; }
    int getSpeedPersec() { return speedPersec; }
    int getVisionRange() { return visionRange; }

    int getPosX() { return position[0]; }
    int getPosY() { return position[1]; }
};

class grayGhost : public ghost
{
public:
    grayGhost(int id)
    {
        ID = id;
    }
};

class redGhost : public ghost
{
public:
    redGhost(int id)
    {
        ID = id;
    }
};

class blueGhost : public ghost
{
public:
    blueGhost(int id)
    {
        ID = id;
    }
    void teleportToEye(int x, int y)
    {
        position[0] = x;
        position[1] = y;
    }
};

#endif