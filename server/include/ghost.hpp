#ifndef GHOST_H
#define GHOST_H
/**
 * Clase ghost que representa a la base de los enemigos del juego
 */
class ghost
{
private:
    int ruta[10];
    /**
     * Variable que almacena la posición del enemigo
     */
    int position[2];
    /**
     * Variable que contiene la velocidad de movimiento del enemigo
     */
    int speed;

public:
    void moveTo(int x, int y);
    /**
     * Constructor de la clase ghost
     */
    ghost()
    {
    }
    /**
     * Destructor de la clase ghost
     */
    ~ghost() {}
};

class grayGhost : public ghost
{
};

class reedGhost : public ghost
{
};

class blueGhost : public ghost
{
};

#endif