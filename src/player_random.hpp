#pragma once

#include "player.hpp"

struct RandomPlayer : public Player
{
    RandomPlayer(int, Piece);
    ~RandomPlayer();
    virtual Move getMove();
}