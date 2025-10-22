#include "BombGem.h"
#include "Board.h"
#include <iostream>

BombGem::BombGem() {
    gemType = 6;
    sprite.setTexture(Gem::gemTextures[5]);
    sprite.setPosition(0, 0);
}

void BombGem::setGem()
{
    gemType = 6;
    sprite.setTexture(Gem::gemTextures[5]);
}

void BombGem::setGemType(int)
{
    gemType = 6;
}

int BombGem::getGemType()
{
    return gemType;
}

void BombGem::setPosition(float xPosition, float yPosition)
{
    sprite.setPosition(xPosition, yPosition);
}

void BombGem::draw(RenderWindow& window)
{
    window.draw(sprite);
}

void BombGem::animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration) {
    startX = startXPosition;
    startY = startYPosition;
    endX = endXPosition;
    endY = endYPosition;
    animDuration = animationDuration;
    animTime = 0.0f;
    animating = true;
}

bool BombGem::updatePosition(float frameElapsed) {


    if (!animating) {
        return false;
    }

    animTime += frameElapsed;

    float easedProgress = animTime / animDuration;

    if (easedProgress >= 1.0f) {

        easedProgress = 1.0f;
        animating = false;
    }

    visualX = startX + (endX - startX) * easedProgress;
    visualY = startY + (endY - startY) * easedProgress;
    setPosition(visualX, visualY);
    return animating;

}

bool BombGem::isAnimating() const {
    return animating;
}

void BombGem::stopAnimation() {

    animating = false;
    setPosition(endX, endY);
}

float BombGem::getVisualY() const {
    return visualY;
}

float BombGem::getVisualX() const {
    return visualX;
}

void BombGem::setVisualY(float newVisualY) {
    visualY = newVisualY;
}

void BombGem::setVisualX(float newVisualX) {
    visualX = newVisualX;
}

void BombGem::explodeArea3x3(int centerRow, int centerCol, Gem* gems[8][8], bool gemsToRemove[8][8]) {

    for (int row = centerRow - 1; row <= centerRow + 1;row++) {
        for (int column = centerCol - 1; column <= centerCol + 1;column++) {
            if (row >= 0 && row < 8 && column >= 0 && column < 8) {
                if (gems[row][column]) {
                    gemsToRemove[row][column] = true;
                }
            }
        }
    }
    gemsToRemove[centerRow][centerCol] = true;
}

void BombGem::explodeCross(int bombRow1, int bombCol1, int bombRow2, int bombCol2, Gem* gems[8][8], bool gemsToRemove[8][8])
{
    if (bombRow1 >= 0 && bombRow1 < 8 && bombCol1 >= 0 && bombCol1 < 8) {
   
        for (int column = 0; column < 8; column++) {
            if (gems[bombRow1][column]) {
                gemsToRemove[bombRow1][column] = true;
            }
        }
        
        for (int row = 0; row < 8;row++) {
            if (gems[row][bombCol1]) {
                gemsToRemove[row][bombCol1] = true;
            }
        }
    }

    if (bombRow2 >= 0 && bombRow2 < 8 && bombCol2 >= 0 && bombCol2 < 8) {
     
        for (int column = 0; column < 8;column++) {
            if (gems[bombRow2][column]) {
                gemsToRemove[bombRow2][column] = true;
            }
        }
      
        for (int row = 0; row < 8;row++) {
            if (gems[row][bombCol2]) {
                gemsToRemove[row][bombCol2] = true;
            }
        }
    }
}

