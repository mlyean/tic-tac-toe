#pragma once

#include "player.hpp"

struct HumanPlayer : public Player
{
    HumanPlayer(int, Piece);
    ~HumanPlayer();
    virtual Move getMove();
}