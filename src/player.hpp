#pragma once

#include <string>

#include "piece.hpp"
#include "move.hpp"

struct Player
{
    const Piece piece;
    const int id;

    Player(int, Piece);
    ~Player();
    std::string str() const;
    virtual Move getMove() = 0;
};