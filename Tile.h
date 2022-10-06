#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;


class Tile {
    bool _hasFlag;
    bool _isRevealed;
    bool _hasMine;
    unsigned char adjacentMines = 0;
    sf::Sprite _mine;
    sf::Sprite _flag;
    sf::Sprite _number;
    sf::Sprite _tileBack;
    sf::Sprite _tileCover;
    // vector<Tile*> adjacentTiles;
    // Tile* neighbors[8];
public:
    Tile();

    bool IsFlagged();

    bool HasMine();

    bool IsRevealed();

    unsigned int GetMinesAdjacent();

    void Flag();

    void Reset();

    void SetMine();

    void Reveal();

    void AddMinesAdjacent();

    sf::Sprite GetSpriteTileCover();

    sf::Sprite GetSpriteTileBack();

    sf::Sprite GetSpriteFlag();

    sf::Sprite GetSpriteMine();

    sf::Sprite GetSpriteNumber();

    void SetPosition(float x, float y);
};


#endif
