#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Game{
private:

	RenderWindow* window;
	Event event;
	Texture backgroundTexture;
	Sprite backgroundSprite;
	
public:

	Game();
	~Game();

	void runGame();
	void firstWindow();
	void secondWindow();
	void thirdWindow(int finalScore);
};

