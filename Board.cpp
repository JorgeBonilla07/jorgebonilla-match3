#include "Board.h"
#include <iostream>
using namespace std;

Board::Board()   {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            gems[i][j] = nullptr;
        }
    }

    init();
    movesLeft = 20;
    destroyedIceCount = 0;
    score = 0;
    removedGemsCount = 0;
}

Board::~Board() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete gems[i][j];
        }
    }
}

void Board::init() {

    const float icePercentage = 0.05f;
    const int totalCells = 64;
    int iceCount = totalCells * icePercentage;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (gems[i][j]) {
                delete gems[i][j];
            }
            gems[i][j] = nullptr;
        }
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (gems[row][col] == nullptr) {
                gems[row][col] = new NormalGem();
                gems[row][col]->setGem();
                gems[row][col]->setPosition(col * tileSize, row * tileSize);
            }
        }
    }

    prepareBoard();

    int placedIceBlocks = 0;

    while (placedIceBlocks < iceCount) {
        int row = rand() % 8;
        int col = rand() % 8;

        delete gems[row][col];
        gems[row][col] = nullptr;

        if (gems[row][col] == nullptr) {
            gems[row][col] = new IceGem();
            gems[row][col]->setPosition(col * tileSize, row * tileSize);
            placedIceBlocks++;
        }
    }
}

void Board::drawInBoard(RenderWindow& window) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (gems[i][j]) {
                gems[i][j]->draw(window);
            }
        }
    }
}

void Board::swapGems(int firstRow, int firstCol, int secondRow, int secondCol) {

    if (!gems[firstRow][firstCol] || !gems[secondRow][secondCol]) {
        return;
    }
    if (gems[firstRow][firstCol]->getGemType() < 0 || gems[secondRow][secondCol]->getGemType() < 0) {
        return;
    }

    float firstX = firstCol * tileSize;
    float firstY = firstRow * tileSize;
    float secondX = secondCol * tileSize;
    float secondY = secondRow * tileSize;

    gems[firstRow][firstCol]->animateGemMovement(firstX, firstY, secondX, secondY, animSpeed);
    gems[secondRow][secondCol]->animateGemMovement(secondX, secondY, firstX, firstY, animSpeed);

    swap(gems[firstRow][firstCol], gems[secondRow][secondCol]);
}

bool Board::hasMatchAt(int row, int column) {

    if (!gems[row][column]) {
        return false;
    }

    int type = gems[row][column]->getGemType();

    if (type < 0) {
        return false;
    }

    int horizontalCount = 1;

    for (int checkColumn = column - 1; checkColumn >= 0 && gems[row][checkColumn] && gems[row][checkColumn]->getGemType() == type; checkColumn--) {
        horizontalCount++;
    }

    for (int checkColumn = column + 1; checkColumn < 8 && gems[row][checkColumn] && gems[row][checkColumn]->getGemType() == type; checkColumn++) {
        horizontalCount++;
    }

    int verticalCount = 1;

    for (int checkRow = row - 1; checkRow >= 0 && gems[checkRow][column] && gems[checkRow][column]->getGemType() == type; checkRow--) {
        verticalCount++;
    }

    for (int checkRow = row + 1; checkRow < 8 && gems[checkRow][column] && gems[checkRow][column]->getGemType() == type; checkRow++) {
        verticalCount++;
    }

    if (verticalCount >= 3 || horizontalCount >= 3) {

        return true;
    }

    return false;
}

bool Board::markHorizontalMatches(bool GemsToRemove[8][8], bool bombToCreate[8][8]) {
    bool foundMatch = false;

    for (int row = 0; row < 8; row++) {
        int column = 0;

        while (column < 8) {

            while (column < 8 && (!gems[row][column] || gems[row][column]->getGemType() < 0)) {
                column++;
            }

            if (column >= 8) {
                break;
            }

            int type = gems[row][column]->getGemType();
            int startCol = column;
            int endCol = column;

            while (endCol + 1 < 8 && gems[row][endCol + 1] && gems[row][endCol + 1]->getGemType() == type) {
                endCol++;
            }

            int count = endCol - startCol + 1;

            if (count >= 3) {

                foundMatch = true;

                for (int k = startCol; k <= endCol; k++) {

                    if (gems[row][k])
                        GemsToRemove[row][k] = true;
                }

                if (count >= 4) {
                    int bombCol = (startCol + endCol) / 2;

                    if (GemsToRemove[row][bombCol] && gems[row][bombCol] && gems[row][bombCol]->getGemType() >= 0) {
                        bombToCreate[row][bombCol] = true;
                    }
                }

            }
            column = endCol + 1;
        }
    }
    return foundMatch;
}

bool Board::markVerticalMatches(bool GemsToRemove[8][8], bool bombToCreate[8][8]) {
    bool foundMatch = false;

    for (int column = 0; column < 8; column++) {

        int row = 0;
        while (row < 8) {

            while (row < 8 && (!gems[row][column] || gems[row][column]->getGemType() < 0)) {
                row++;
            }

            if (row >= 8) {
                break;
            }

            int type = gems[row][column]->getGemType();
            int startRow = row;
            int endRow = row;

            while (endRow + 1 < 8 && gems[endRow + 1][column] && gems[endRow + 1][column]->getGemType() == type) {
                endRow++;
            }
            int count = endRow - startRow + 1;

            if (count >= 3) {
                foundMatch = true;

                for (int k = startRow; k <= endRow; ++k) {

                    if (gems[k][column])
                        GemsToRemove[k][column] = true;
                }

                if (count > 3) {
                    int bombRow = (startRow + endRow) / 2;

                    if (GemsToRemove[bombRow][column] && gems[bombRow][column] && gems[bombRow][column]->getGemType() >= 0) {
                        bombToCreate[bombRow][column] = true;
                    }
                }


            }
            row = endRow + 1;
        }
    }
    return foundMatch;
}

bool Board::processMatches(bool hitIce) {

    bool bombToCreate[8][8] = { false };
    bool gemsToRemove[8][8] = { false };
    bool foundHorizontal = markHorizontalMatches(gemsToRemove, bombToCreate);
    bool foundVertical = markVerticalMatches(gemsToRemove, bombToCreate);

    bool foundMatch = foundHorizontal || foundVertical;

    if (foundMatch) {

        int gemTypeToCount = 0;
        int gemCount = countMarkedColor(gemsToRemove, gemTypeToCount);

        if (gemCount > 0) {
            removedGemsCount += gemCount;
        }
        if (hitIce) {
            hitIceIfAdjacent(gemsToRemove);
        }
        calculateScore(gemsToRemove);
        refillBoard(gemsToRemove, bombToCreate);
    }

    return foundMatch;
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

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (gemsToRemove[row][column]) {
                actualScore += 10;

            }
        }
    }

    score += actualScore;
}

int Board::getScore()  const {
    return score;
}

int Board::getDestroyedIceCount() const
{
    return destroyedIceCount;
}

int Board::getRemovedGemsCount() const
{
    return removedGemsCount;
}

int Board::countMarkedColor(const bool gemsToRemove[8][8], int gemType)
{
    if (!gemsToRemove) {
        return 0;
    }

    int count = 0;
    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {

            if (gemsToRemove[row][column] && gems[row][column] && gems[row][column]->getGemType() == gemType) {
                count++;
            }
        }
    }
    return count;
}

void Board::refillBoard(bool GemsToRemove[8][8], bool bombToCreate[8][8]) {

    try {

        // Se usa cuando llamamos al metodo sin parametros, como en 
        if (!GemsToRemove && !bombToCreate) {
            bool tempRemove[8][8] = { false };
            bool tempBombs[8][8] = { false };
            refillBoard(tempRemove, tempBombs);
            return;
        }

        // borra todas las gemas de GemsToRemove
        for (int row = 0; row < 8; row++) {
            for (int column = 0; column < 8; column++) {
                if (GemsToRemove[row][column] && gems[row][column]) {

                    if (gems[row][column]->getGemType() < 0) {
                        destroyedIceCount++;
                    }
                    delete gems[row][column];
                    gems[row][column] = nullptr;
                }
            }
        }

        // Se crean las gemas bomba 
        for (int column = 0; column < 8; column++) {
            for (int row = 0; row < 8; row++) {
                if (bombToCreate && bombToCreate[row][column] && GemsToRemove[row][column]) {
                    int spawnRow = 0;

                    while (spawnRow < 8 && gems[spawnRow][column]) {
                        spawnRow++;
                    }

                    if (spawnRow < 8) {
                        createBombGem(spawnRow, column, row);
                    }
                    else {
                        if (!gems[row][column]) {
                            gems[row][column] = new BombGem();
                            gems[row][column]->setPosition(column * tileSize, row * tileSize);
                        }
                    }
                }
            }
        }

        for (int column = 0; column < 8; column++) {
            int writeRow = 7;

            for (int readRow = 7; readRow >= 0; readRow--) {

                if (gems[readRow][column] && gems[readRow][column]->getGemType() >= 0) {

                    while (writeRow > readRow && gems[writeRow][column]) {
                        writeRow--;
                    }

                    if (writeRow != readRow) {

                        gems[writeRow][column] = gems[readRow][column];
                        gems[readRow][column] = nullptr;
                        gems[writeRow][column]->animateGemMovement(column * tileSize, readRow * tileSize, column * tileSize, writeRow * tileSize, animSpeed);
                    }
                    writeRow--;
                }
                // El bloque de hielo no deja caer gemas
                else if (gems[readRow][column] && gems[readRow][column]->getGemType() < 0) {
                    writeRow = readRow - 1;
                }
            }

            for (int row = writeRow; row >= 0; row--) {

                if (!gems[row][column]) {

                    gems[row][column] = new NormalGem();
                    gems[row][column]->setGem();
                    gems[row][column]->setPosition(column * tileSize, row * tileSize);
                    gems[row][column]->animateGemMovement(column * tileSize, -tileSize, column * tileSize, row * tileSize, animSpeed);
                }
            }
        }

        //Luego de todo el proceso, se asegura la posicion logica 
        for (int row = 0; row < 8; row++) {
            for (int column = 0; column < 8; column++) {
                if (gems[row][column]) {
                    gems[row][column]->setPosition(column * tileSize, row * tileSize);
                }
            }
        }
    }

    catch (...) {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (gems[row][col]) {
                    delete gems[row][col];
                    gems[row][col] = nullptr;
                }
            }
        }
        throw "Board::refillBoard: excepción durante refillBoard";
    }
}

bool Board::updateFallingGems(float frameElapsed) {

    bool anyAnimating = false;

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (gems[row][column] && gems[row][column]->isAnimating()) {
                if (gems[row][column]->updatePosition(frameElapsed)) {
                    anyAnimating = true;
                }
            }
        }
    }
    return anyAnimating;
}

void Board::hitIceIfAdjacent(bool gemsToRemove[8][8]) {

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (gems[row][col] && gems[row][col]->getGemType() < 0) {

                bool adyacente = false;

                for (int checkRow = 0; checkRow < 8 && !adyacente; checkRow++) {
                    for (int checkColumn = 0; checkColumn < 8 && !adyacente; checkColumn++) {
                        if (gemsToRemove[checkRow][checkColumn] && areAdjacent(row, col, checkRow, checkColumn)) {

                            adyacente = true;
                        }
                    }
                }
                if (adyacente) {

                    IceGem* ice = (IceGem*)gems[row][col];
                    ice->hit();

                    if (ice->getHitsLeft() <= 0) {

                        delete gems[row][col];
                        gems[row][col] = nullptr;
                        destroyedIceCount++;
                    }
                }
            }
        }
    }
}

void Board::triggerEffect(int bombRow, int bombCol, int targetRow, int targetCol, int targetGemType, bool gemsToRemove[8][8])
{
    BombGem::explodeArea3x3(targetRow, targetCol, gems, gemsToRemove);

    if (targetGemType == 6) {

        BombGem::explodeCross(bombRow, bombCol, targetRow, targetCol, gems, gemsToRemove);
    }
}

void Board::createBombGem(int spawnRow, int column, int destRow) {

    if (spawnRow < 0 || spawnRow >= 8 || destRow < 0 || destRow >= 8 || column < 0 || column >= 8) {
        return;
    }

    if (gems[spawnRow][column]) {
        delete gems[spawnRow][column];
        gems[spawnRow][column] = nullptr;
    }
    if (gems[destRow][column]) {
        delete gems[destRow][column];
        gems[destRow][column] = nullptr;
    }

    gems[spawnRow][column] = new BombGem();
    
    if (spawnRow == destRow) {
        gems[spawnRow][column]->setPosition(column * tileSize, destRow * tileSize);
        //////////////////////////////////////
    }
    else {
        gems[spawnRow][column]->setPosition(column * tileSize, -tileSize);
        gems[spawnRow][column]->animateGemMovement(column * tileSize, -tileSize, column * tileSize, destRow * tileSize, 0.4f);
    }
}

void Board::activateBombGem(int bombRow, int bombCol, int targetRow, int targetCol, int targetGemType) {

    bool gemsToRemove[8][8] = { false };
    triggerEffect(bombRow, bombCol, targetRow, targetCol, targetGemType, gemsToRemove);

    if (targetGemType >= 0) {
        int removedOfTarget = countMarkedColor(gemsToRemove, targetGemType);
        if (removedOfTarget > 0) {
            removedGemsCount += removedOfTarget;
        }
    }

    calculateScore(gemsToRemove);
    refillBoard(gemsToRemove);
}

int Board::getGemTypeAt(int row, int col) const {

    if (row < 0 || row >= 8 || col < 0 || col >= 8 || !gems[row][col]) {
        return -99;
    }
    return gems[row][col]->getGemType();
}

//Metodo para limpiar el tablero antes de la primera jugada
void Board::clearBombGems() {
    bool anyBomb = false;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (gems[row][col] && gems[row][col]->getGemType() == 6) {

                delete gems[row][col];
                gems[row][col] = nullptr;
                anyBomb = true;
            }
        }
    }

    if (anyBomb) {
        refillBoard();
    }
}

void Board::prepareBoard() {

    while (processMatches(false));
    clearBombGems();


    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (gems[row][col]) {
                gems[row][col]->setPosition(col * tileSize, row * tileSize);
                gems[row][col]->stopAnimation();
            }
        }
    }
}




