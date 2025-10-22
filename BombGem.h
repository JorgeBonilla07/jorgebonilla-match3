#pragma once
#include "Gem.h"
using namespace std;

class BombGem : public Gem {

public:
    BombGem();
    void setGem() override;
    void setGemType(int) override;
    int getGemType() override;
    void setPosition(float xPosition, float yPosition) override;
    void draw(RenderWindow& window) override;

    void animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration) override;
    bool updatePosition(float frameElapsed) override;
    bool isAnimating() const override;
    void stopAnimation() override;
    float getVisualY() const override;
    float getVisualX() const override;
    void setVisualY(float newVisualY) override;
    void setVisualX(float newVisualX) override;

    static void explodeArea3x3(int centerRow, int centerCol, Gem* gems[8][8], bool gemsToRemove[8][8]);
    static void explodeCross(int bombRow1, int bombCol1, int bombRow2, int bombCol2, Gem* gems[8][8], bool gemsToRemove[8][8]);
};

