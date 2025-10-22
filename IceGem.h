#pragma once
#include "Gem.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class IceGem : public Gem
{
private:

	Texture iceTexture;
	Sprite iceSprite;
	int hitsLeft;

public:

	IceGem();

	void setGem() override;
	void setGemType(int) override;
	int getGemType() override;
	void setPosition(float xPosition, float yPosition) override;
	void draw(RenderWindow& window) override;
	void hit();
	int getHitsLeft();
};

