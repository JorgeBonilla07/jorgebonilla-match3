#include "Level.h"

Level::Level() {

    objectiveType = ObjectiveType::ReachScore;
    objectiveQuantity = 0;
    colorGem = -1;
    challengeDescrip = "undefined";
}

Level::Level(ObjectiveType type, int quantity, string newDescrip, int newColor) {
    objectiveType = type;
    objectiveQuantity = quantity;
    colorGem = newColor;
    challengeDescrip = newDescrip;
}