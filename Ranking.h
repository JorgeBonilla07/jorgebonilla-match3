#pragma once
#include "Player.h"

class Ranking
{
private:
	Player* players;
	int count;
	int maxEntries;
public:

	Ranking();
	~Ranking();

	void addPlayer(Player newPlayer);
	void addScoreForPlayer(string playerName, int score);
	void sortDescendingByScore();
	bool saveToFile();
	bool loadFromFile();
	string showRanking();
};

