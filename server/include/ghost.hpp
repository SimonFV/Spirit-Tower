#ifndef GHOST_H
#define GHOST_H
/**
 * Clase ghost que representa a la base de los enemigos del juego
 */
class ghost
{
private:
    /**
     * Variable que almacena la posición del enemigo
     */
    int position[2];
    /**
     * Variable que contiene la velocidad de movimiento del enemigo
     */
    int speed;

public:
    /**
     * Constructor de la clase ghost
     */
    ghost() {}
    /**
     * Destructor de la clase ghost
     */
    ~ghost() {}
};

/**
 * Clase hija de la clase ghost
 */
class ghostNormal : public ghost
{
};
#endif