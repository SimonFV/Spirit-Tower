#ifndef PLAYER_H
#define PLAYER_H
/**
 * @brief Clase player que representa al jugador del juego.
 */
class player
{
private:
    /**
     * @note Variable que alamacena la posición actual del jugador.
     */
    int position[2];
    /**
     * @note Variable que alamacena la posición anterior del jugador.
     */
    int lastPosition[2];
    /**
     * @note Variable que alamacena la vida del jugador.
     */
    int life;

public:
    /**
     * @note Constructor de la clase player
     */
    player()
    {
        position[0] = 0;
        position[1] = 0;
        lastPosition[0] = 0;
        lastPosition[1] = 0;
        life = 5;
    }
    /**
     * @note Destructor de la clase player
     */
    ~player() {}

public:
    void moveTo(int x, int y)
    {
        position[0] = x;
        position[1] = y;
    }
    void setLastPos(int x, int y)
    {
        lastPosition[0] = x;
        lastPosition[1] = y;
    }
    void setLife(int l)
    {
        life = l;
    }

public:
    /**
     * @brief Método que retorna la vida del jugador.
     */
    int getLife() { return life; }
    /**
     * @brief Método que retorna la posición en X del jugador.
     */
    int getPosX() { return position[0]; }
    /**
     * @brief Método que retorna la posición en Y del jugador.
     */
    int getPosY() { return position[1]; }
    /**
     * @brief Método que retorna la posición en X del jugador.
     */
    int getLastPosX() { return lastPosition[0]; }
    /**
     * @brief Método que retorna la posición en Y del jugador.
     */
    int getLastPosY() { return lastPosition[1]; }
};

#endif