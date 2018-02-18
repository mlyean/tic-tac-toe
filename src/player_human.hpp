#pragma once

#include "player.hpp"

struct HumanPlayer : public Player
{
    HumanPlayer(int, Piece);                        // HumanPlayer constructor
    HumanPlayer(int, Piece, const std::string&);
    ~HumanPlayer();                                 // HumanPlayer destructor
    virtual Move getMove(const Board&);             // Return a move made by HumanPlayer
};