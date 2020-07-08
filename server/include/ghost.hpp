#ifndef GHOST_H
#define GHOST_H

class ghost
{
private:
    int ruta[10];
    int position[2];
    int speed;

public:
    void moveTo(int x, int y);
    ghost() {}
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