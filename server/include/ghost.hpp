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
<<<<<<< HEAD
    void moveTo(int x, int y);
=======
    /**
     * Constructor de la clase ghost
     */
>>>>>>> b725276867f9950c9fb06536e2ff8fdf42b3e12f
    ghost()
    {
    }
    /**
     * Destructor de la clase ghost
     */
    ~ghost() {}
};

<<<<<<< HEAD
class grayGhost : public ghost
=======
/**
 * Clase hija de la clase ghost
 */
class ghostNormal : public ghost
>>>>>>> b725276867f9950c9fb06536e2ff8fdf42b3e12f
{
};

class reedGhost : public ghost
{
};

class blueGhost : public ghost
{
};

#endif