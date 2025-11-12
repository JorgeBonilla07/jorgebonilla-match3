#include "Ranking.h"
#include <fstream>
#include <string>

Ranking::Ranking()
{
    maxEntries = 20;
    players = new Player[maxEntries];
    count = 0;
}

Ranking::~Ranking()
{
    delete[] players;
    players = nullptr;
    count = 0;
}

void Ranking::addPlayer(Player newPlayer)
{
    if (count < maxEntries) {
        players[count] = newPlayer;
        count++;
    }
}

void Ranking::addScoreForPlayer(string playerName, int score)
{

    if (playerName.empty()) {
        return;
    }

    for (int i = 0; i < count; i++) {

        if (players[i].getName() == playerName) {
            int newScore = players[i].getScore() + score;
            players[i].setScore(newScore);
            return;
        }
    }
}

void Ranking::sortDescendingByScore()
{
    if (count <= 1) {
        return;
    }

    for (int i = 0; i < count - 1;i++) {
        for (int j = 0; j < count - 1 - i;j++) {
            if (players[j].getScore() < players[j+1].getScore()) {
                Player temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }
}

bool Ranking::saveToFile()
{
    ofstream outputFile;
    outputFile.open("ranking.txt",ios::out|ios::trunc);

    if (!outputFile.is_open()) {
        cerr << "NO SE PUEDE ABRIR EL ARCHIVO" << endl;
        return false;
    }

    for (int i = 0; i < count;i++) {        
        outputFile << players[i].getName() << ':' << players[i].getScore() <<endl;
    }

    outputFile.close();

    cout << "DATOS GUARDADOS EXITOSAMENTE EN EL ARCHIVO." << endl;
    return true;
}

bool Ranking::loadFromFile()
{
    ifstream inputFile("ranking.txt");

    if (!inputFile.is_open()) {
        return false; 
    }

    string lineText;
    count = 0;

    while (getline(inputFile, lineText) && count < maxEntries) {

        if (lineText.size() == 0) {
            continue;
        }

        size_t markerPosition = lineText.rfind(':');

        if (markerPosition == string::npos) {
            continue;
        }

        string playerName = lineText.substr(0, markerPosition);
        string scoreText = lineText.substr(markerPosition + 1);

        try {
            int score = stoi(scoreText);
            players[count] = Player(playerName, score);
            count++;
        }
        catch (...) {
            continue;
        }
    }
    inputFile.close();
    return true;
}

string Ranking::showRanking()
{
    int limit = 0;

    if (count < 10) {
        limit = count;
    }
    else {
        limit = 10;
    }

    string playerInfo;
    for (int i = 0; i < limit; i++) {

       if (!playerInfo.empty()) {
                playerInfo += '\n';
       }

       playerInfo += to_string(i + 1);
       playerInfo += ". ";
       playerInfo += players[i].getName();
       playerInfo += " - ";
       playerInfo += to_string(players[i].getScore());
       playerInfo += " PTS";
    }

    return playerInfo;
}

