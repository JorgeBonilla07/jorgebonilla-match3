#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gems[i][j] = nullptr;
        }
    }

    init();
    score = 0;
    movesLeft = 20;
}

Board::~Board() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete gems[i][j];
        }
    }
}

void Board::init() {

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            if (gems[row][col]) {
                delete gems[row][col];
            }
                gems[row][col] = new Gem();
                gems[row][col]->setGem();
                gems[row][col]->setPosition(col * 64.0f, row * 64.0f);
        }
    }
    while (processMatches()) {};

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            if (gems[row][col]) {

                gems[row][col]->setPosition(col * 64.0f, row * 64.0f);
                gems[row][col]->stopAnimation();
            }
        }
    }
}

void Board::drawInBoard(sf::RenderWindow& window) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gems[i][j]->draw(window);
        }
    }
}

bool Board::areAdjacent(int firstRow, int firstCol, int secondRow, int secondCol) {

    return (abs(firstRow - secondRow) == 1 && firstCol == secondCol) || (abs(firstCol - secondCol) == 1 && firstRow == secondRow);
}

void Board::decrementMoves() {

    if (movesLeft > 0) {
        movesLeft--;
    }
}

int Board::getMovesLeft() {

    return movesLeft;
}

void Board::calculateScore(bool gemsToRemove[8][8]) {

    int actualScore = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (gemsToRemove[i][j]) {
                actualScore += 10;
            }
        }
    }

    score += actualScore;
}

int Board::getScore() {
    return score;
}

void Board::swapGems(int firstRow, int firstCol, int secondRow, int secondCol) {
    
    float firstX = firstCol * 64.0f;
    float firstY = firstRow * 64.0f;
    float secondX = secondCol * 64.0f;
    float secondY = secondRow * 64.0f;

    gems[firstRow][firstCol]->animateGemMovement(firstX, firstY, secondX, secondY, 0.5f);
    gems[secondRow][secondCol]->animateGemMovement(secondX, secondY, firstX, firstY, 0.5f);

    swap(gems[firstRow][firstCol], gems[secondRow][secondCol]); 
}

bool Board::hasMatchAt(int row, int column) {

    int type = gems[row][column]->getGemType();

    if (type < 0) {
        return false;
    }

    int horizontalCount = 1;
    for (int checkColumn = column - 1; checkColumn >= 0 && gems[row][checkColumn]->getGemType() == type; checkColumn--) {

        horizontalCount++;
    }
    for (int checkColumn = column + 1; checkColumn < 8 && gems[row][checkColumn]->getGemType() == type; checkColumn++) {

        horizontalCount++;
    }

    int verticalCount = 1;
    for (int checkRow = row - 1; checkRow >= 0 && gems[checkRow][column]->getGemType() == type; checkRow--) {

        verticalCount++;
    }
    for (int checkRow = row + 1; checkRow < 8 && gems[checkRow][column]->getGemType() == type; checkRow++) {

        verticalCount++;
    }
    if (verticalCount >= 3 || horizontalCount >= 3) {

        return true;
    }

    return false;
}

bool Board::markHorizontalMatches(bool GemsToRemove[8][8]) {

    bool foundMatch = false;

    for (int row = 0; row < 8; row++) {

        int column = 0;

        while (column < 8) {

            int type = gems[row][column]->getGemType();

            int startCol = column;

            while (column + 1 < 8 && gems[row][column + 1]->getGemType() == type) {

                column++;
            }

            int matchLength = column - startCol + 1;

            if (matchLength >= 3) {

                foundMatch = true;

                for (int k = startCol; k <= column; k++) {

                    GemsToRemove[row][k] = true;
                }
            }

            column++;
        }
    }
    return foundMatch;
}

bool Board::markVerticalMatches(bool GemsToRemove[8][8]) {

    bool foundMatch = false;

    for (int column = 0; column < 8; column++) {

        int row = 0;

        while (row < 8) {

            int type = gems[row][column]->getGemType();

            int startRow = row;

            while (row + 1 < 8 && gems[row + 1][column]->getGemType() == type) {

                row++;
            }

            int matchLength = row - startRow + 1;

            if (matchLength >= 3) {

                foundMatch = true;

                for (int k = startRow; k <= row; ++k) {

                    GemsToRemove[k][column] = true;
                }
            }

            row++;
        }
    }
    return foundMatch;
}

bool Board::processMatches() {
   
    bool GemsToRemove[8][8] = { false };
    bool foundHorizontal = markHorizontalMatches(GemsToRemove);
    bool foundVertical = markVerticalMatches(GemsToRemove);

    bool foundMatch = foundHorizontal || foundVertical;

    if (foundMatch) {

        calculateScore(GemsToRemove);
        refillBoard(GemsToRemove);
    }

    return foundMatch;
}

void Board::refillBoard(bool GemsToRemove[8][8]) {

	for (int column = 0; column < 8; column++) {

        int targetRow = 7;

        for (int row = 7; row >= 0; row--) {
            if (!GemsToRemove[row][column]) {
                if (targetRow != row) {

                    gems[targetRow][column]->setGemType(gems[row][column]->getGemType());
                    gems[targetRow][column]->animateGemMovement(column * 64.0f, gems[row][column]->getVisualY(),column * 64.0f, targetRow * 64.0f,0.4f);
                }
                targetRow--;
            }
        }
        for (int row = targetRow; row >= 0; row--) {

            gems[row][column]->setGem();
            gems[row][column]->animateGemMovement(column * 64.0f, -64.0f, column * 64.0f, row * 64.0f, 0.4f);
                
        }
    }
    
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {

            gems[row][column]->setPosition(column * 64.0f, row * 64.0f);
        }
    }
}

bool Board::updateFallingGems(float frameElapsed) {

    bool anyAnimating = false;

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8;column++) {
            if (gems[row][column]->isAnimating()) {
                if (gems[row][column]->updatePosition(frameElapsed)) {
                    anyAnimating = true;
                }
            }
        }
    }
    return anyAnimating;
}