#pragma once
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "NormalGem.h"
#include "IceGem.h"
#include "BombGem.h"

class Board {
private:

    Gem* gems[8][8];
    int score;
    int movesLeft;
    int destroyedIceCount;
    int removedGemsCount;
    static constexpr float tileSize = 64.0f;
    static constexpr float animSpeed = 0.25f;

public:

    Board();
    ~Board();

    void init();
    void drawInBoard(RenderWindow& window);
    void swapGems(int firstRow, int firstCol, int secondRow, int secondCol);
    bool hasMatchAt(int row, int col);
    bool markHorizontalMatches(bool GemsToRemove[8][8], bool bombToCreate[8][8]);
    bool markVerticalMatches(bool GemsToRemove[8][8], bool bombToCreate[8][8]);
    bool processMatches(bool hitIce);
    void refillBoard(bool toRemove[8][8] = nullptr, bool bombToCreate[8][8] = nullptr);
    bool updateFallingGems(float frameElapsed);
    bool areAdjacent(int firstRow, int firstCol, int secondRow, int secondCol);
    void hitIceIfAdjacent(bool gemsToRemove[8][8]);

    void triggerEffect(int bombRow, int bombCol, int targetRow, int targetCol, int targetGemType, bool gemsToRemove[8][8]);
    void createBombGem(int spawnRow, int row, int column);
    void activateBombGem(int bombRow, int bombCol, int targetRow, int targetCol, int targetType);

    int getGemTypeAt(int row, int col) const;
    void clearBombGems();
    void prepareBoard();
    int getScore() const;
    void decrementMoves();
    int getMovesLeft();
    int getDestroyedIceCount() const;
    int getRemovedGemsCount() const;
    int countMarkedColor(const bool gemsToRemove[8][8], int gemType);
    void calculateScore(bool gemsToRemove[8][8]);
};
