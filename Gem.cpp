#include "Gem.h"
#include <iostream>
using namespace std;

Texture Gem::gemTextures[6];

void Gem::loadTextures() {

    gemTextures[0].loadFromFile("assets/pinkGem.png");
    gemTextures[1].loadFromFile("assets/greenGem.png");
    gemTextures[2].loadFromFile("assets/blueGem.png");
    gemTextures[3].loadFromFile("assets/redGem.png");
    gemTextures[4].loadFromFile("assets/goldenGem.png");
    gemTextures[5].loadFromFile("assets/bombGem.png");
}