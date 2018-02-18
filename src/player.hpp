#pragma once

#include <string>

#include "board.hpp"
#include "piece.hpp"
#include "move.hpp"

struct Player
{
    const int id;                               // Id of the player
    const Piece piece;                          // Piece used by the player

    Player(int, Piece);                         // Player constructor
    ~Player();                                  // Player destructor
    virtual Move getMove(const Board&) = 0;     // Return a move made by the player
    std::string str() const;                    // Return the string representation
};