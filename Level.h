#pragma once
#include <iostream>
using namespace std;

enum class ObjectiveType {
	ReachScore,
	DestroyIceBlocks,
	RemoveColorGems
};

class Level
{
public:

	ObjectiveType objectiveType;
	int objectiveQuantity;
	int colorGem;                  // Only for RemoveColorGems (0=red, 1=green, etc.), -1 if not used
	string challengeDescrip;        // Challenge description for display

	Level();
	Level(ObjectiveType type, int quantity, string newDescrip, int newColor = -1);
};

