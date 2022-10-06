#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "TextureManager.h"
#include "Random.h"
#include "Tile.h"
#include "Board.h"

using namespace std;

int main() {
    Board board;
    board.ConfigBoard();
    board.SetDimensions(board.GetColumns(), board.GetRows(), board.GetMines());

    sf::RenderWindow window(sf::VideoMode(board.GetColumns() * 32, (board.GetRows() * 32) + 100), "Minesweeper");

    sf::Sprite buttonFaceHappy(TextureManager::GetTexture("face_happy"));
    buttonFaceHappy.setPosition((board.GetColumns() * 16) - 32, board.GetRows() * 32);
    sf::Sprite buttonFaceWin(TextureManager::GetTexture("face_win"));
    buttonFaceWin.setPosition((board.GetColumns() * 16) - 32, board.GetRows() * 32);
    sf::Sprite buttonFaceLose(TextureManager::GetTexture("face_lose"));
    buttonFaceLose.setPosition((board.GetColumns() * 16) - 32, board.GetRows() * 32);

    sf::Sprite debugSprite(TextureManager::GetTexture("debug"));
    debugSprite.setPosition((board.GetColumns() * 32) - 256, board.GetRows() * 32);

    sf::Sprite test1Sprite(TextureManager::GetTexture("test_1"));
    test1Sprite.setPosition((board.GetColumns() * 32) - 192, board.GetRows() * 32);

    sf::Sprite test2Sprite(TextureManager::GetTexture("test_2"));
    test2Sprite.setPosition((board.GetColumns() * 32) - 128, board.GetRows() * 32);

    sf::Sprite test3Sprite(TextureManager::GetTexture("test_3"));
    test3Sprite.setPosition((board.GetColumns() * 32) - 64, board.GetRows() * 32);

    sf::Sprite digit1Sprite(TextureManager::GetTexture("digits"));
    digit1Sprite.setPosition(63, board.GetRows() * 32);

    sf::Sprite digit2Sprite(TextureManager::GetTexture("digits"));
    digit2Sprite.setPosition(42, board.GetRows() * 32);

    sf::Sprite digit3Sprite(TextureManager::GetTexture("digits"));
    digit3Sprite.setPosition(21, board.GetRows() * 32);

    sf::Sprite digitNegSprite(TextureManager::GetTexture("digits"));
    digitNegSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
    digitNegSprite.setPosition(0, board.GetRows() * 32);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                bool button;
                if (event.mouseButton.button == sf::Mouse::Left) {
                    button = true;
                    if (buttonFaceHappy.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ||
                        buttonFaceWin.getGlobalBounds().contains(mousePosition.x, mousePosition.y) ||
                        buttonFaceLose.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        board.Reset();
                    } else if (debugSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        board.DebugMode();
                    } else if (test1Sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        board.ChangeBoard("boards/testboard1.brd");
                    } else if (test2Sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        board.ChangeBoard("boards/testboard2.brd");
                    } else if (test3Sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        board.ChangeBoard("boards/testboard3.brd");
                    } else {
                        board.MousePress(mousePosition.x, mousePosition.y, button);
                    }

                }
                if (event.mouseButton.button == sf::Mouse::Right) {
                    button = false;
                    board.MousePress(mousePosition.x, mousePosition.y, button);
                }
            }
        }

        window.clear();

        int digits = board.GetMines() - board.GetFlags();
        if (digits < 0) {
            digits = digits * -1;
        }
        digit1Sprite.setTextureRect(sf::IntRect(((digits % 10) * 21), 0, 21, 32));
        digit2Sprite.setTextureRect(sf::IntRect((((digits / 10) % 10) * 21), 0, 21, 32));
        digit3Sprite.setTextureRect(sf::IntRect((((digits / 100) % 10) * 21), 0, 21, 32));

        board.Draw(window);
        if (board.GetGameState() == 0) {
            window.draw(buttonFaceHappy);
        } else if (board.GetGameState() == 1) {
            window.draw(buttonFaceLose);
        } else if (board.GetGameState() == 2) {
            window.draw(buttonFaceWin);
        }
        window.draw(debugSprite);
        window.draw(test1Sprite);
        window.draw(test2Sprite);
        window.draw(test3Sprite);
        window.draw(digit1Sprite);
        window.draw(digit2Sprite);
        window.draw(digit3Sprite);
        if (board.GetMines() < board.GetFlags()) {
            window.draw(digitNegSprite);
        }
        window.display();
    }
    TextureManager::Clear();
    return 0;
}