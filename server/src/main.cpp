
#include <game.hpp>
#include <signal.h>
#include <stdio.h>

using namespace std;

int main()
{
    game::getInstance()->run_game();
    return 0;
}