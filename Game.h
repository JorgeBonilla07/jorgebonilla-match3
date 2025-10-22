#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Board.h"
using namespace sf;

class Game {
private:

	static const int numLevels = 3;
	Level levels[numLevels];
	int currentLevel;

	RenderWindow* window;
	Event event;
	Texture backgroundTexture;
	Sprite backgroundSprite;
	void animateAndRedraw(Board& board, Sprite& scoreIconSprite, Text& scoreText, Text& movesText, Sprite& levelBoxSprite, Text& levelText, Text& challengeDescription, Text& challengeProgressText, Sprite& challengeBoxSprite);

public:

	Game();
	~Game();

	void runGame();
	void firstWindow();
	void secondWindow();
	void thirdWindow(int finalScore, bool levelCompleted = false);
	string getObjectiveProgress(const Board& board) const;
};