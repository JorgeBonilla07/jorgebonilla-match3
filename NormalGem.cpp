#include "NormalGem.h"
#include <cstdlib>

NormalGem::NormalGem() {
    gemType = 0;
    visualX = 0.0f;
    visualY = 0.0f;
    startX = 0.0f;
    startY = 0.0f;
    endX = 0.0f;
    endY = 0.0f;
    animTime = 0.0f;
    animDuration = 0.0f;
    animating = false;
}

void NormalGem::setGem() {
    gemType = rand() % 5;
    sprite.setTexture(Gem::gemTextures[gemType]);
}

void NormalGem::setGemType(int newGemType) {
    gemType = newGemType;
    sprite.setTexture(Gem::gemTextures[gemType]);
}

int NormalGem::getGemType() {
    return gemType;
}

void NormalGem::setPosition(float xPosition, float yPosition) {

    sprite.setPosition(xPosition, yPosition);
    visualX = xPosition;
    visualY = yPosition;
}

void NormalGem::draw(RenderWindow& window) {
    window.draw(sprite);
}

void NormalGem::setVisualY(float newVisualY) {
    visualY = newVisualY;
}

void NormalGem::setVisualX(float newVisualX) {
    visualX = newVisualX;
}

float NormalGem::getVisualY() const {
    return visualY;
}

void NormalGem::animateGemMovement(float startXPosition, float startYPosition, float endXPosition, float endYPosition, float animationDuration) {
    startX = startXPosition;
    startY = startYPosition;
    endX = endXPosition;
    endY = endYPosition;
    animDuration = animationDuration;
    animTime = 0.0f;
    animating = true;
}

bool NormalGem::updatePosition(float frameElapsed) {

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
    sprite.setPosition(visualX, visualY);
    return animating;
}

bool NormalGem::isAnimating() const {

    return animating;
}

void NormalGem::stopAnimation() {

    animating = false;

    if (endX == 0.0f && endY == 0.0f) {
        sprite.setPosition(visualX, visualY);
    }
    else {
        visualX = endX;
        visualY = endY;
        sprite.setPosition(visualX, visualY);
    }
}