#pragma once

#include "player.hpp"

struct RandomPlayer : public Player
{
    RandomPlayer(int, Piece);       // RandomPlayer constructor
    ~RandomPlayer();                // RandomPlayer destructor
    virtual Move getMove(const Board&);    // Return a move made by RandomPlayer
};