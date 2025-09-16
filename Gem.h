#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Gem {
private:
    int gemType;
    Sprite sprite;
    static Texture gemTextures[5];
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
    Gem();
    void setGem();
    void setGemType(int newGemType);
    int getGemType();
    void setPosition(float xPosition, float yPosition);
    void draw(RenderWindow& window);
    static void loadTextures();
    void setVisualY(float newVisualY);
	void setVisualX(float newVisualX);
    float getVisualY();
    void animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration);
    bool updatePosition(float frameElapsed);
    bool isAnimating();
    void stopAnimation();
};
