#include "Tile.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

Tile::Tile() {
    Reset();
}

bool Tile::IsFlagged() {
    return _hasFlag;
}

bool Tile::HasMine() {
    return _hasMine;
}

bool Tile::IsRevealed() {
    return _isRevealed;
}

void Tile::Reveal() {
    _isRevealed = true;
}

unsigned int Tile::GetMinesAdjacent() {
    return adjacentMines;
}

void Tile::AddMinesAdjacent() {
    adjacentMines++;
}

void Tile::Flag() {
    if (_isRevealed == false) {
        _hasFlag = !_hasFlag;
    }
}

void Tile::Reset() {
    _hasFlag = false;
    _hasMine = false;
    _isRevealed = false;
    adjacentMines = 0;
}

void Tile::SetMine() {
    _hasMine = true;
}

sf::Sprite Tile::GetSpriteTileCover() {
    return _tileCover;
}

sf::Sprite Tile::GetSpriteTileBack() {
    return _tileBack;
}

sf::Sprite Tile::GetSpriteFlag() {
    return _flag;
}

sf::Sprite Tile::GetSpriteNumber() {
    if (adjacentMines == 1) {
        _number.setTexture(TextureManager::GetTexture("number_1"));
    } else if (adjacentMines == 2) {
        _number.setTexture(TextureManager::GetTexture("number_2"));
    } else if (adjacentMines == 3) {
        _number.setTexture(TextureManager::GetTexture("number_3"));
    } else if (adjacentMines == 4) {
        _number.setTexture(TextureManager::GetTexture("number_4"));
    } else if (adjacentMines == 5) {
        _number.setTexture(TextureManager::GetTexture("number_5"));
    } else if (adjacentMines == 6) {
        _number.setTexture(TextureManager::GetTexture("number_6"));
    } else if (adjacentMines == 7) {
        _number.setTexture(TextureManager::GetTexture("number_7"));
    } else if (adjacentMines == 8) {
        _number.setTexture(TextureManager::GetTexture("number_8"));
    }
    return _number;
}

sf::Sprite Tile::GetSpriteMine() {
    return _mine;
}

void Tile::SetPosition(float x, float y) {
    _tileBack.setTexture(TextureManager::GetTexture("tile_revealed"));
    _tileCover.setTexture(TextureManager::GetTexture("tile_hidden"));
    _mine.setTexture(TextureManager::GetTexture("mine"));
    _flag.setTexture(TextureManager::GetTexture("flag"));

    _number.setPosition(x, y);
    _tileBack.setPosition(x, y);
    _tileCover.setPosition(x, y);
    _mine.setPosition(x, y);
    _flag.setPosition(x, y);

}