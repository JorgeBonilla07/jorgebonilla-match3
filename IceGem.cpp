#include "IceGem.h"

IceGem::IceGem()
{
	gemType = -1;
	hitsLeft = 2;
	iceTexture.loadFromFile("assets/iceBlock.png");
	iceSprite.setTexture(iceTexture);
	iceSprite.setPosition(0, 0);
}

void IceGem::setGem() {
	hitsLeft = 2;
	iceSprite.setTexture(iceTexture);
	gemType = -1;
}

void IceGem::setGemType(int)
{
	gemType = -1;
}

int IceGem::getGemType()
{
	return gemType;
}

void IceGem::setPosition(float xPosition, float yPosition)
{
	iceSprite.setPosition(xPosition, yPosition);
}

void IceGem::draw(RenderWindow& window)
{
	window.draw(iceSprite);
}

void IceGem::hit()
{
	if (hitsLeft > 0) {
		hitsLeft--;
	}
}

int IceGem::getHitsLeft()
{
	return hitsLeft;
}


