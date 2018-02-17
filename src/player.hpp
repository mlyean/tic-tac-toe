#pragma once

#include <string>

#include "piece.hpp"
#include "move.hpp"

class Player
{
private:
    const Piece piece;
    const int id;

public:
    Player(int, Piece);
    ~Player();
    std::string str() const;
    virtual Move getMove() = 0;
}