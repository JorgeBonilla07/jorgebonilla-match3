#pragma once
#include <SFML/Graphics.hpp>
#include "Gem.h"

class Board {
private:

    Gem* gems[8][8];
    int score;
    int movesLeft;

public:

    Board();
    ~Board();

    void init();
    void drawInBoard(sf::RenderWindow& window);
    void swapGems(int firstRow, int firstCol, int secondRow, int secondCol);
    bool hasMatchAt(int row, int col);
    bool markHorizontalMatches(bool GemsToRemove[8][8]);
    bool markVerticalMatches(bool GemsToRemove[8][8]);
    bool processMatches();
    void refillBoard(bool toRemove[8][8]);
    bool updateFallingGems(float frameElapsed);
    int getScore();
    bool areAdjacent(int firstRow, int firstCol, int secondRow, int secondCol);
    void decrementMoves();
    int getMovesLeft();
    void calculateScore(bool gemsToRemove[8][8]);

};
