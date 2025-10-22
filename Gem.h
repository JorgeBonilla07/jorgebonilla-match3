#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Gem {

protected:
    int gemType;
    Sprite sprite;
    static Texture gemTextures[6];
    float visualY;
    float visualX;
    float startY;
    float startX;
    float endY;
    float endX;
    float animTime;
    float animDuration;
    bool animating;

public:

    virtual void setGem() = 0;
    virtual void setGemType(int newGemType) = 0;
    virtual int getGemType() = 0;
    virtual void setPosition(float xPosition, float yPosition) = 0;
    virtual void draw(RenderWindow& window) = 0;

    virtual void setVisualY(float newVisualY) {}
    virtual void setVisualX(float newVisualX) {}
    virtual float getVisualY() const { return 0.0f; }
    virtual float getVisualX() const { return 0.0f; }
    virtual void animateGemMovement(float, float, float, float, float) {}
    virtual bool updatePosition(float) { return false; }
    virtual bool isAnimating() const { return false; }
    virtual void stopAnimation() {}

    static void loadTextures();
};
