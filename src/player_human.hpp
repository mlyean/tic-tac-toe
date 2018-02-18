#pragma once

#include "player.hpp"

struct HumanPlayer : public Player
{
    HumanPlayer(int, Piece);        // HumanPlayer constructor
    ~HumanPlayer();                 // HumanPlayer destructor
    virtual Move getMove(Board);    // Return a move made by HumanPlayer
};