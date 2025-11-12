#pragma once
#include <iostream>
using namespace std;

class Player
{
private:
	string name;
	int score;

public:

	Player();
	Player(string newName, int newScore);

	void setScore(int newScore);

	string getName();
	int getScore();
};