#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#pragma once

#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Board {
    unsigned int columns;
    unsigned int rows;
    unsigned int mines;
    unsigned char gameState = 0;
    vector<Tile> tiles;
    bool debugModeOn = false;
public:
    Board();

    unsigned int GetColumns();

    unsigned int GetRows();

    unsigned char GetGameState();

    unsigned int GetFlags();

    unsigned int GetMines();

    void Draw(sf::RenderWindow &window);

    void FlagTile(unsigned int column, unsigned int row);

    void RevealTile(int column, int row);

    void OpenRecursion(int x, int y);

    void Reset();

    void Shuffle();

    void ConfigBoard();

    void ChangeBoard(string boardName);

    void DebugMode();

    void SetDimensions(unsigned int totColumns, unsigned int totRows, unsigned int totMines);

    void MousePress(float x, float y, bool button);
};

#endif //MINESWEEPER_BOARD_H