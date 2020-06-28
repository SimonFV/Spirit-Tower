#ifndef GHOST_H
#define GHOST_H

class ghost
{
private:
    int position[2];
    int speed;

public:
    ghost() {}
    ~ghost() {}
};

class ghostNormal : public ghost
{
};
#endif