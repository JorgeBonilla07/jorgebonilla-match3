#include "Gem.h"
#include <cstdlib>
using namespace std;

Texture Gem::gemTextures[5];

Gem::Gem() {

    gemType = 0;
    visualY = 0.0f;
    visualX = 0.0f;
    startY = 0.0f;
	startX = 0.0f;
    endY = 0.0f;
	endX = 0.0f;
    animTime = 0.0f;
    animDuration = 0.0f;
    animating = false;
    sprite.setTexture(gemTextures[gemType]);
}

void Gem::loadTextures() {

    gemTextures[0].loadFromFile("assets/pinkGem.png");
    gemTextures[1].loadFromFile("assets/greenGem.png");
    gemTextures[2].loadFromFile("assets/blueGem.png");
    gemTextures[3].loadFromFile("assets/redGem.png");
    gemTextures[4].loadFromFile("assets/goldenGem.png");
}

void Gem::setVisualY(float newVisualY) {

    visualY = newVisualY;
}

void Gem::setVisualX(float newVisualX){

	visualX = newVisualX;
}

float Gem::getVisualY() {
    return visualY;
}

void Gem::animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration) {
    startX = startXPosition;
    startY = startYPosition;
    endX = endXPosition;
    endY = endYPosition;
    animDuration = animationDuration;
    animTime = 0.0f;
    animating = true;
}

bool Gem::updatePosition(float frameElapsed){

    if (!animating) {
        return false;
    }

    animTime += frameElapsed;

    float progress = min(animTime / animDuration, 1.0f);

    float easedProgress = 1.0f - (1.0f - progress) * (1.0f - progress);

    visualX = startX + (endX - startX) * easedProgress;
    visualY = startY + (endY - startY) * easedProgress;

    if (progress >= 1.0f) {

        visualX = endX;
        visualY = endY;
        animating = false;
    }

    return animating;
}

void Gem::setGem() {

    gemType = rand() % 5;
    sprite.setTexture(gemTextures[gemType]);
}

void Gem::setGemType(int newGemType) {
    gemType = newGemType;
    sprite.setTexture(gemTextures[gemType]);
}

int Gem::getGemType() {
    return gemType;
}

void Gem::setPosition(float xPosition, float yPosition) {

    sprite.setPosition(xPosition, yPosition);// situa logicamente la gema
    
	// hace que la logica y la visual esten iguales al inicio
	visualX = xPosition; 
	visualY = yPosition;
}

void Gem::draw(RenderWindow& window) {

    Vector2f originalPos = sprite.getPosition();
    sprite.setPosition(visualX, visualY);
    window.draw(sprite);

}

bool Gem::isAnimating() {

    return animating;
}

void Gem::stopAnimation() {

    animating = false;
    visualX = sprite.getPosition().x;
    visualY = sprite.getPosition().y;
}
