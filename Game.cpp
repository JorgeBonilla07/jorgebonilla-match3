#include "Game.h"
#include "Board.h"
#include "Gem.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Game::Game() {}

Game::~Game() {

    delete this->window;
}

void Game::runGame() {

    firstWindow();
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

    if (!backgroundTexture.loadFromFile("assets/background.png")) {

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
    scoreIconSprite.setPosition(432, 10);
    scoreIconSprite.setScale(0.8f, 0.8f);

    Font scoreFont;
    if (!scoreFont.loadFromFile("assets/japaneseFont.ttf")) {

        cout << " ERROR AL CARGAR LA FUENTE" << endl;
    }

    Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(sf::Color(218, 165, 32));
    scoreText.setPosition(590, 100);

    Font movesFont;
    if (!movesFont.loadFromFile("assets/japaneseFont.ttf")) {

        cout << " ERROR AL CARGAR LA FUENTE" << endl;
    }
    Text movesText;
    movesText.setFont(movesFont);
    movesText.setCharacterSize(35);
    movesText.setFillColor(sf::Color(218, 165, 32));
    movesText.setPosition(590, 235);

    int firstRow = -1;
    int firstCol = -1;
    bool hasFirst = false;

    while (window->isOpen()) {

        while (window->pollEvent(event)) {

            if (event.type == Event::Closed) {
                window->close();
            }

            if (board.getMovesLeft() <= 0) {

                window->close();
                thirdWindow(board.getScore());
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
                            
                            board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);

                                Clock clock;
                                while (board.updateFallingGems(clock.restart().asSeconds())) {

                                    window->clear();
                                    window->draw(backgroundSprite);
                                    board.drawInBoard(*window);
                                    window->draw(scoreIconSprite);
                                    window->draw(scoreText);
                                    window->draw(movesText);
                                    window->display();
                                    sleep(milliseconds(15));
                                }
                            

                            if (board.hasMatchAt(firstRow, firstCol) || board.hasMatchAt(selectedRow, selectedColumn)) {

                                board.decrementMoves();

                                while (board.processMatches()) {

                                    cout << "SE DETECTO MATCH" << endl;

                                    Clock clock;

                                    while (board.updateFallingGems(clock.restart().asSeconds())) {

                                        window->clear();
                                        window->draw(backgroundSprite);
                                        board.drawInBoard(*window);
                                        window->draw(scoreIconSprite);
                                        window->draw(scoreText);
                                        window->draw(movesText);
                                        window->display();
                                        sleep(milliseconds(15));
                                    }
                                }
                            }
                            else {
                                
                                board.swapGems(firstRow, firstCol, selectedRow, selectedColumn);

                                Clock clock;

                                while (board.updateFallingGems(clock.restart().asSeconds())) {

                                    window->clear();
                                    window->draw(backgroundSprite);
                                    board.drawInBoard(*window);
                                    window->draw(scoreIconSprite);
                                    window->draw(scoreText);
                                    window->draw(movesText);
                                    window->display();
                                    sleep(milliseconds(15));
                                }

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

        scoreText.setString(to_string(board.getScore()) + ".pts");
        movesText.setString(to_string(board.getMovesLeft()));
        window->clear();
        window->draw(backgroundSprite);
        board.drawInBoard(*window);
        window->draw(scoreIconSprite);
        window->draw(scoreText);
        window->draw(movesText);
        window->display();
    }
}


void Game::thirdWindow(int finalScore)
{
    window = new RenderWindow(VideoMode(800, 600), "FIN DEL JUEGO");

    if (!backgroundTexture.loadFromFile("assets/background.png")) {

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
	Text finalText;
	finalText.setFont(finalTextFont);
	finalText.setCharacterSize(35);
	finalText.setFillColor(sf::Color(218, 165, 32));
	finalText.setPosition(277, 90);
	finalText.setString("PUNTAJE FINAL:");

	Font scoreFont;
	if (!scoreFont.loadFromFile("assets/japaneseFont.ttf")) {

		cout << " ERROR AL CARGAR LA FUENTE" << endl;
	}
	Text scoreText;
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color(218, 165, 32));
	scoreText.setPosition(330, 150);

	Texture playAgainTexture;
    if(!playAgainTexture.loadFromFile("assets/playAgainBotton.png")) {

        cout << "ERROR AL CARGAR LA IMAGEN DEL BOTÓN DE JUGAR DE NUEVO" << endl;
	}
	Sprite playAgainSprite;
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

                if (playAgainSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                    window->close();
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
		window->draw(finalText);
		window->draw(scoreText);
        window->draw(playAgainSprite);
		window->draw(exitSprite);
		scoreText.setString(to_string(finalScore) + ".pts");
        window->display();
    }
}
