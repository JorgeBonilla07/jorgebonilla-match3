#include "Game.h"
#include "Board.h"
#include "Gem.h"
#include "NormalGem.h"
#include "IceGem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

void Game::animateAndRedraw(Board& board, Sprite& scoreIconSprite, Text& scoreText, Text& movesText, Sprite& levelBoxSprite, Text& levelText, Text& challengeDescription, Text& challengeProgressText, Sprite& challengeBoxSprite)
{
    Clock clock;
    while (board.updateFallingGems(clock.restart().asSeconds())) {

        window->clear();
        window->draw(backgroundSprite);
        board.drawInBoard(*window);
        window->draw(scoreIconSprite);
        window->draw(scoreText);
        window->draw(movesText);
        window->draw(levelBoxSprite);
        window->draw(levelText);
        window->draw(challengeBoxSprite);
        window->draw(challengeDescription);
        window->draw(challengeProgressText);
        window->display();
    }
}

Game::Game() : currentLevel(0), window(nullptr), event() {

    levels[0] = Level(ObjectiveType::ReachScore, 1000, "Alcanza 1000 puntos.");
    levels[1] = Level(ObjectiveType::DestroyIceBlocks, 2, "Destrue 2\nbloques de hielo.");
    levels[2] = Level(ObjectiveType::RemoveColorGems, 20, "Elimina 20\ngemas rosas.", 0);
}

Game::~Game() {

    delete this->window;
}

void Game::runGame() {

    firstWindow();
}

string Game::getObjectiveProgress(const Board& board) const {

    const Level& level = levels[currentLevel];
    int progress = 0;
    int target = level.objectiveQuantity;
    string text;

    switch (level.objectiveType) {

    case ObjectiveType::ReachScore:

        progress = min(board.getScore(), target);
        text = to_string(progress) + "/" + to_string(target) + " pts";
        break;

    case ObjectiveType::DestroyIceBlocks:

        progress = min(board.getDestroyedIceCount(), target);
        text = to_string(progress) + "/" + to_string(target) + " hielos\ndestruidos";
        break;

    case ObjectiveType::RemoveColorGems:

        progress = min(board.getRemovedGemsCount(), target);
        text = to_string(progress) + "/" + to_string(target) + "\ngemas eliminadas";
        break;

    default:

        text = "Desafío desconocido";
        break;
    }
    return text;
}

void Game::firstWindow() {

    window = new RenderWindow(VideoMode(800, 600), "GEMAS ENCANTADAS");

    if (!backgroundTexture.loadFromFile("assets/background.png")) {

        cout << "ERROR AL CARGAR LA IMAGEN DE EL FONDO";
    }
    backgroundSprite.setTexture(backgroundTexture);


    Texture playButtonTexture;
    Sprite playButtonSprite;

    if (!playButtonTexture.loadFromFile("assets/playBotton.png")) {

        cout << "ERROR AL CARGAR LA IMAGEN DEL BOTÓN";
    }
    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition(275, 315);
    playButtonSprite.setScale(0.5f, 0.5f);

    Texture titleTexture;
    Sprite titleSprite;
    if (!titleTexture.loadFromFile("assets/title.png")) {

        cout << "ERROR AL CARGAR LA IMAGEN DEL TITULO";
    }
    titleSprite.setTexture(titleTexture);
    titleSprite.setPosition(190, 20);
    titleSprite.setScale(0.8f, 0.8f);


    while (window->isOpen()) {

        while (window->pollEvent(event)) {

            if (event.type == Event::Closed) {

                window->close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {

                Vector2i mousePosition = Mouse::getPosition(*window);

                if (playButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                    window->close();
                    secondWindow();
                }
            }
        }

        window->clear();
        window->draw(backgroundSprite);
        window->draw(playButtonSprite);
        window->draw(titleSprite);
        window->display();
    }
}

void Game::secondWindow() {

    window = new RenderWindow(VideoMode(800, 600), "GEMAS ENCANTADAS");

    if (!backgroundTexture.loadFromFile("assets/background2.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DE EL FONDO";
    }
    backgroundSprite.setTexture(backgroundTexture);

    Gem::loadTextures();
    Board board;

    Texture scoreIconTexture;
    if (!scoreIconTexture.loadFromFile("assets/scoreImage.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL ICONO DE PUNTAJE" << endl;
    }
    Sprite scoreIconSprite;
    scoreIconSprite.setTexture(scoreIconTexture);
    scoreIconSprite.setPosition(550, 110);
    scoreIconSprite.setScale(0.52f, 0.52f);

    Font scoreFont;
    if (!scoreFont.loadFromFile("assets/japaneseFont.ttf")) {
        cout << " ERROR AL CARGAR LA FUENTE" << endl;
    }

    Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color(218, 165, 32));
    scoreText.setPosition(590, 200);

    Font movesFont;
    if (!movesFont.loadFromFile("assets/japaneseFont.ttf")) {
        cout << " ERROR AL CARGAR LA FUENTE" << endl;
    }
    Text movesText;
    movesText.setFont(movesFont);
    movesText.setCharacterSize(35);
    movesText.setFillColor(Color(218, 165, 32));
    movesText.setPosition(635, 350);

    Texture levelBoxTexture;
    if (!levelBoxTexture.loadFromFile("assets/levelBox.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL RECUADRO DE NIVEL" << endl;
    }
    Sprite levelBoxSprite;
    levelBoxSprite.setTexture(levelBoxTexture);
    levelBoxSprite.setPosition(535, -2);
    levelBoxSprite.setScale(0.4f, 0.4f);

    Text levelText;
    levelText.setFont(scoreFont);
    levelText.setCharacterSize(30);
    levelText.setFillColor(Color(218, 165, 32));
    levelText.setPosition(611, 55);
    levelText.setString("NIVEL " + to_string(currentLevel + 1));

    Texture challengeBoxTexture;
    if (!challengeBoxTexture.loadFromFile("assets/challengeBox.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL RECUADRO DE NIVEL" << endl;
    }
    Sprite challengeBoxSprite;
    challengeBoxSprite.setTexture(challengeBoxTexture);
    challengeBoxSprite.setPosition(500, 345);
    challengeBoxSprite.setScale(0.77f, 0.77f);

    Text challengeDescription;
    challengeDescription.setFont(scoreFont);
    challengeDescription.setCharacterSize(20);
    challengeDescription.setFillColor(Color(218, 165, 32));
    challengeDescription.setString(levels[currentLevel].challengeDescrip);
    challengeDescription.setPosition(550, 450);

    Text challengeProgressText;
    challengeProgressText.setFont(scoreFont);
    challengeProgressText.setCharacterSize(20);
    challengeProgressText.setFillColor(Color(218, 165, 32));
    challengeProgressText.setString(getObjectiveProgress(board));
    challengeProgressText.setPosition(550, 505);

    int firstRow = -1;
    int firstCol = -1;
    bool hasFirst = false;

    bool bombSwapPending = false;
    int bombRow = -1;
    int bombCol = -1;
    int otherGemRow = -1;
    int otherGemCol = -1;
    int otherGemType = -1;

    while (window->isOpen()) {
        while (window->pollEvent(event)) {

            if (event.type == Event::Closed) {
                window->close();
            }
            if (board.getMovesLeft() <= 0) {

                const Level& lvl = levels[currentLevel];
                bool levelCompleted = false;

                switch (lvl.objectiveType) {
                case ObjectiveType::ReachScore:
                    if (board.getScore() >= lvl.objectiveQuantity) {
                        levelCompleted = true;
                    }
                    break;
                case ObjectiveType::DestroyIceBlocks:
                    if (board.getDestroyedIceCount() >= lvl.objectiveQuantity) {
                        levelCompleted = true;
                    }
                    break;
                case ObjectiveType::RemoveColorGems:
                    if (board.getRemovedGemsCount() >= lvl.objectiveQuantity) {
                        levelCompleted = true;
                    }
                    break;
                default:
                    break;
                }

                window->close();
                thirdWindow(board.getScore(), levelCompleted);
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(*window);
                int selectedColumn = mousePosition.x / 64;
                int selectedRow = mousePosition.y / 64;

                if (selectedRow >= 0 && selectedRow < 8 && selectedColumn >= 0 && selectedColumn < 8) {

                    if (!hasFirst) {
                        firstRow = selectedRow;
                        firstCol = selectedColumn;
                        hasFirst = true;
                    }
                    else {
                        if (board.areAdjacent(firstRow, firstCol, selectedRow, selectedColumn)) {

                            int firstType = board.getGemTypeAt(firstRow, firstCol);
                            int secondType = board.getGemTypeAt(selectedRow, selectedColumn);

                            bool isBombAndBomb = (firstType == 6 && secondType == 6);
                            bool isBombAndNormal = ((firstType == 6 && secondType >= 0 && secondType <= 4) || (secondType == 6 && firstType >= 0 && firstType <= 4));

                            if (isBombAndBomb) {

                                board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);
                                bombSwapPending = true;

                                bombRow = firstRow;
                                bombCol = firstCol;
                                otherGemRow = selectedRow;
                                otherGemCol = selectedColumn;
                                otherGemType = 6;

                            }
                            else if (isBombAndNormal) {

                                board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);
                                bombSwapPending = true;

                                if (firstType == 6) {
                                    bombRow = firstRow;
                                    bombCol = firstCol;
                                    otherGemRow = selectedRow;
                                    otherGemCol = selectedColumn;
                                    otherGemType = secondType;
                                }
                                else {
                                    bombRow = selectedRow;
                                    bombCol = selectedColumn;
                                    otherGemRow = firstRow;
                                    otherGemCol = firstCol;
                                    otherGemType = firstType;
                                }
                            }
                            else {

                                board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);
                            }

                            Clock clock;
                            while (board.updateFallingGems(clock.restart().asSeconds())) {
                                animateAndRedraw(board, scoreIconSprite, scoreText, movesText, levelBoxSprite, levelText, challengeDescription, challengeProgressText, challengeBoxSprite);
                            }

                            if (bombSwapPending) {

                                board.activateBombGem(bombRow, bombCol, otherGemRow, otherGemCol, otherGemType);
                                bombSwapPending = false;

                                board.decrementMoves();
                                animateAndRedraw(board, scoreIconSprite, scoreText, movesText, levelBoxSprite, levelText, challengeDescription, challengeProgressText, challengeBoxSprite);
                                cout << "LA BOMBA HA EXPLOTADO!" << endl;

                                while (board.processMatches(true)) {
                                    animateAndRedraw(board, scoreIconSprite, scoreText, movesText, levelBoxSprite, levelText, challengeDescription, challengeProgressText, challengeBoxSprite);
                                    cout << "SE DETECTO MATCH" << endl;
                                }
                            }

                            else if (board.hasMatchAt(firstRow, firstCol) || board.hasMatchAt(selectedRow, selectedColumn)) {
                                board.decrementMoves();
                                while (board.processMatches(true)) {
                                    animateAndRedraw(board, scoreIconSprite, scoreText, movesText, levelBoxSprite, levelText, challengeDescription, challengeProgressText, challengeBoxSprite);
                                    cout << "SE DETECTO MATCH" << endl;
                                }
                            }
                            else {

                                board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);
                                animateAndRedraw(board, scoreIconSprite, scoreText, movesText, levelBoxSprite, levelText, challengeDescription, challengeProgressText, challengeBoxSprite);
                                cout << "NO SE DETECTO MATCH" << endl;
                            }

                        }
                        else {
                            cout << "SOLO PUEDES INTERCAMBIAR GEMAS ADYACENTES" << endl;
                        }
                        hasFirst = false;
                    }
                }
            }
        }

        scoreText.setString(to_string(board.getScore()) + " PTS");
        movesText.setString(to_string(board.getMovesLeft()));
        challengeProgressText.setString(getObjectiveProgress(board));

        window->clear();
        window->draw(backgroundSprite);
        board.drawInBoard(*window);
        window->draw(scoreIconSprite);
        window->draw(scoreText);
        window->draw(movesText);
        window->draw(levelBoxSprite);
        window->draw(levelText);
        window->draw(challengeBoxSprite);
        window->draw(challengeDescription);
        window->draw(challengeProgressText);
        window->display();
    }
}

void Game::thirdWindow(int finalScore, bool levelCompleted)
{
    window = new RenderWindow(VideoMode(800, 600), "FIN DEL NIVEL");

    if (!backgroundTexture.loadFromFile("assets/background2.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DE EL FONDO" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    Texture finalScoreBox;
    if (!finalScoreBox.loadFromFile("assets/finalScoreBox.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL ICONO DE PUNTAJE" << endl;
    }
    Sprite finalScoreSprite;
    finalScoreSprite.setTexture(finalScoreBox);
    finalScoreSprite.setPosition(155, 10);
    finalScoreSprite.setScale(0.8f, 0.8f);

    Font finalTextFont;
    if (!finalTextFont.loadFromFile("assets/japaneseFont.ttf")) {
        cout << " ERROR AL CARGAR LA FUENTE" << endl;
    }

    Text mainText;
    mainText.setFont(finalTextFont);
    mainText.setCharacterSize(25);
    mainText.setFillColor(Color(218, 165, 32));
    mainText.setPosition(235, 115);

    if (levelCompleted) {
        mainText.setString("        NIVEL " + to_string(currentLevel + 1) + " COMPLETADO");
    }
    else {
        mainText.setString("  NO COMPLETASTE EL NIVEL");
    }

    Text scoreText;
    scoreText.setFont(finalTextFont);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color(218, 165, 32));
    scoreText.setPosition(330, 150);
    scoreText.setString(to_string(finalScore) + " PTS");

    Texture playNextTexture;
    Sprite playNextSprite;
    bool hasPlayNext = false;
    if (levelCompleted && (currentLevel + 1) < 3) {
        if (playNextTexture.loadFromFile("assets/nextLevelBotton.png")) {
            playNextSprite.setTexture(playNextTexture);
            playNextSprite.setPosition(145, 290);
            playNextSprite.setScale(0.5f, 0.5f);
            hasPlayNext = true;
        }
    }

    Texture playAgainTexture;
    Sprite playAgainSprite;
    if (!playAgainTexture.loadFromFile("assets/playAgainBotton.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL BOTÓN DE JUGAR DE NUEVO" << endl;
    }
    playAgainSprite.setTexture(playAgainTexture);
    playAgainSprite.setPosition(145, 290);
    playAgainSprite.setScale(0.5f, 0.5f);

    Texture exitTexture;
    if (!exitTexture.loadFromFile("assets/exitGameBotton.png")) {
        cout << "ERROR AL CARGAR LA IMAGEN DEL BOTÓN DE SALIR" << endl;
    }
    Sprite exitSprite;
    exitSprite.setTexture(exitTexture);
    exitSprite.setPosition(420, 290);
    exitSprite.setScale(0.5f, 0.5f);

    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == Event::Closed) {
                window->close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePosition = Mouse::getPosition(*window);

                if (hasPlayNext && playNextSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    window->close();

                    if (currentLevel + 1 < 3) {
                        currentLevel++;
                    }
                    secondWindow();
                }
                else if (playAgainSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    window->close();

                    if (currentLevel == 2) {
                        currentLevel = 0;
                    }
                    secondWindow();
                }

                if (exitSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    window->close();
                }
            }
        }

        window->clear();
        window->draw(backgroundSprite);
        window->draw(finalScoreSprite);
        window->draw(mainText);
        window->draw(scoreText);
        if (hasPlayNext) {
            window->draw(playNextSprite);
        }
        else {
            window->draw(playAgainSprite);
        }
        window->draw(exitSprite);
        window->display();
    }
}
