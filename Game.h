#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Board.h"
#include "Ranking.h"
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
	void animateAndRedraw(Sprite& levelBottonSprite,Board& board, Sprite& scoreIconSprite, Text& scoreText, Text& movesText, Sprite& levelBoxSprite, Text& levelText, Text& challengeDescription, Text& challengeProgressText, Sprite& challengeBoxSprite);
	string currentPlayerName;
	Ranking ranking;

public:

	Game();
	~Game();

	void runGame();
	void firstWindow();
	void secondWindow();
	void thirdWindow(int finalScore, bool levelCompleted = false);
	void rankingWindow();
	void registerWindow();
	void levelsWindow();

	string getObjectiveProgress(const Board& board) const;
};