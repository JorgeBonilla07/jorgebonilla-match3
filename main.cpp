#include "Game.h"
#include "Gem.h"
#include <cstdlib>

int main()
{
    srand(time(0));

    Gem::loadTextures();

    Game match3;
    match3.runGame();
    return 0;
}
