#include "Player.h"

Player::Player()
	:name("UNDEFINED"), score(0)
{
}

Player::Player(string newName, int newScore)
	:name(newName), score(newScore)
{
}

void Player::setScore(int newScore)
{
	score = newScore;
}

string Player::getName()
{
	return name;
}

int Player::getScore()
{
	return score;
}

