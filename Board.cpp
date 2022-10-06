#include "Board.h"
#include "Random.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Board::Board() {
    columns = 25;
    rows = 16;
    mines = 50;
}

unsigned int Board::GetColumns() {
    return columns;
}

unsigned int Board::GetRows() {
    return rows;
}

unsigned int Board::GetMines() {
    return mines;
}

unsigned char Board::GetGameState() {
    return gameState;
}

unsigned int Board::GetFlags() {
    unsigned int totalFlags = 0;
    for (unsigned int i = 0; i < tiles.size(); i++) {
        totalFlags += tiles[i].IsFlagged();
    }
    return totalFlags;
}

void Board::DebugMode() {
    debugModeOn = !debugModeOn;
    if (gameState != 0) {
        debugModeOn = false;
    }
}

void Board::ConfigBoard() {
    ifstream File("boards/config.cfg");

    if (File.is_open()) {
        string lineFromFile;

        for (short i = 0; i < 3; i++) {
            getline(File, lineFromFile);
            if (i == 0) {
                columns = stoi(lineFromFile);
            }
            if (i == 1) {
                rows = stoi(lineFromFile);
            }
            if (i == 2) {
                mines = stoi(lineFromFile);
            }
        }
        File.close();
    } else {
        cout << "File not opened." << endl;
    }
}

void Board::ChangeBoard(string boardName) {
    gameState = 0;
    for (Tile &tile: tiles) {
        tile.Reset();
    }

    ifstream File(boardName);

    if (File.is_open()) {
        string lineFromFile;

        int tempRow = 0;
        int minesHere = 0;
        while (getline(File, lineFromFile)) {
            for (int i = 0; i < lineFromFile.length(); i++) {
                if (lineFromFile.at(i) == '1') {
                    tiles[i + columns * tempRow].SetMine();
                    minesHere++;
                }
            }
            tempRow++;
        }
        mines = minesHere;
        File.close();
    } else {
        cout << "File not opened." << endl;
    }

    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            if (tiles[jj + columns * ii].HasMine() == false) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if ((i == 0 && j == 0) || (i + jj < 0 || j + ii < 0 || columns == i + jj || rows == j + ii)) {
                            continue;
                        }
                        if (tiles[(i + jj) + columns * (j + ii)].HasMine() == true) {
                            tiles[jj + columns * ii].AddMinesAdjacent();
                        }
                    }
                }
            }
        }
    }
}

void Board::SetDimensions(unsigned int totColumns, unsigned int totRows, unsigned int totMines) {
    columns = totColumns;
    rows = totRows;
    mines = totMines;
    gameState = 0;
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < columns; j++) {
            tiles.push_back(Tile());
        }
    }
    for (unsigned int i = 0; i < mines; i++) {
        unsigned int xMine = Random::Int(0, columns - 1);
        unsigned int yMine = Random::Int(0, rows - 1);
        if (tiles[xMine + columns * yMine].HasMine() == true) {
            i--;
        } else {
            tiles[xMine + columns * yMine].SetMine();
        }
    }

    for (long ii = 0; ii < rows; ii++) {
        for (long jj = 0; jj < columns; jj++)
            if (tiles[jj + columns * ii].HasMine() == false) {
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        if ((i == 0 && j == 0) || (i + jj < 0 || j + ii < 0 || columns == i + jj || rows == j + ii)) {
                            continue;
                        } else {
                            if (tiles[(i + jj) + columns * (j + ii)].HasMine() == true) {
                                tiles[jj + columns * ii].AddMinesAdjacent();
                            }
                        }
                    }
                }
            }
    }
}

void Board::Shuffle() {
    for (unsigned int i = 0; i < mines; i++) {
        unsigned int xMine = Random::Int(0, columns - 1);
        unsigned int yMine = Random::Int(0, rows - 1);
        if (tiles[xMine + columns * yMine].HasMine() == true) {
            i--;
        } else {
            tiles[xMine + columns * yMine].SetMine();
        }
    }

    for (int ii = 0; ii < rows; ii++) {
        for (int jj = 0; jj < columns; jj++) {
            if (tiles[jj + columns * ii].HasMine() == false) {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if ((i == 0 && j == 0) || (i + jj < 0 || j + ii < 0 || columns == i + jj || rows == j + ii)) {
                            continue;
                        }
                        if (tiles[(i + jj) + columns * (j + ii)].HasMine() == true) {
                            tiles[jj + columns * ii].AddMinesAdjacent();
                        }
                    }
                }
            }
        }
    }
}

void Board::Reset() {
    ConfigBoard();
    gameState = 0;
    for (Tile &tile: tiles) {
        tile.Reset();
    }
    Shuffle();
}

void Board::MousePress(float x, float y, bool button) {
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i].GetSpriteTileCover().getGlobalBounds().contains(x, y)) {
            if (button == true) {
                RevealTile((i % columns), (i / columns));
                return;
            } else {
                FlagTile((i % columns), (i / columns));
                return;
            }
        }
    }
}

void Board::FlagTile(unsigned int column, unsigned int row) {
    if (gameState == 0) {
        tiles[column + columns * row].Flag();
    }
}

void Board::RevealTile(int x, int y) {
    if (gameState == 0 && tiles[x + columns * y].IsFlagged() == false) {
        if (tiles[x + columns * y].HasMine() == false) {
            OpenRecursion(x, y);
        } else {
            debugModeOn = false;
            gameState = 1;
        }
    }
    unsigned int totalCoveredCells = 0;
    for (Tile &tile: tiles) {
        totalCoveredCells += 1 - tile.IsRevealed();
    }
    if (mines == totalCoveredCells) {
        gameState = 2;
        debugModeOn = false;
        for (Tile &tile: tiles) {
            if (tile.HasMine() == true) {
                tile.Flag();
            }
        }
    }
}

void Board::OpenRecursion(int x, int y) {
    if (!(x > -1 && y > -1 && x < columns && y < rows) || tiles[x + columns * y].IsRevealed() ||
        tiles[x + columns * y].IsFlagged()) {
        return;
    }
    tiles[x + columns * y].Reveal();
    if (tiles[x + columns * y].GetMinesAdjacent() > 0) {
        return;
    }
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            OpenRecursion((x + j), (y + i));
        }
    }
}

void Board::Draw(sf::RenderWindow &window) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            tiles[j + columns * i].SetPosition(j * 32, i * 32);
            window.draw(tiles[j + columns * i].GetSpriteTileBack());
            if (gameState == 1) {
                if (tiles[j + columns * i].HasMine() == true) {
                    window.draw(tiles[j + columns * i].GetSpriteMine());
                }
                if (tiles[j + columns * i].IsRevealed() == false && tiles[j + columns * i].HasMine() == false) {
                    window.draw(tiles[j + columns * i].GetSpriteTileCover());
                }
            } else if (gameState == 0) {
                if (tiles[j + columns * i].IsRevealed() == false) {
                    window.draw(tiles[j + columns * i].GetSpriteTileCover());
                }
            } else {
                if (tiles[j + columns * i].HasMine() == true) {
                    window.draw(tiles[j + columns * i].GetSpriteTileCover());
                }
            }

            if (tiles[j + columns * i].IsFlagged() == true) {
                window.draw(tiles[j + columns * i].GetSpriteFlag());
            }
            if (tiles[j + columns * i].GetMinesAdjacent() > 0 && tiles[j + columns * i].IsRevealed() == true) {
                window.draw(tiles[j + columns * i].GetSpriteNumber());
            }
            if (gameState == 2 && tiles[j + columns * i].HasMine() == true) {
                window.draw(tiles[j + columns * i].GetSpriteFlag());
            }
            if (debugModeOn == true || gameState == 1) {
                if (tiles[j + columns * i].HasMine() == true) {
                    window.draw(tiles[j + columns * i].GetSpriteMine());
                }
            }

        }
    }
}