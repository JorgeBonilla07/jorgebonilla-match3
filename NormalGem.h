#pragma once
#include "Gem.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class NormalGem : public Gem
{
public:

    NormalGem();

    void setGem() override;
    void setGemType(int newGemType) override;
    int getGemType() override;
    void setPosition(float xPosition, float yPosition) override;
    void draw(RenderWindow& window) override;
    void setVisualY(float newVisualY) override;
    void setVisualX(float newVisualX) override;
    float getVisualY() const override;
    void animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration) override;
    bool updatePosition(float frameElapsed) override;
    bool isAnimating() const override;
    void stopAnimation() override;
};