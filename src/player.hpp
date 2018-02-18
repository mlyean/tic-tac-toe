#pragma once

#include <string>

#include "board.hpp"
#include "piece.hpp"
#include "move.hpp"

struct Player
{
    const int id;                               // Player ID
    const Piece piece;                          // Piece used by the player
    const std::string name;                     // Player name

    Player(int, Piece);
    Player(int, Piece, const std::string&);     // Player constructor
    ~Player();                                  // Player destructor
    virtual Move getMove(const Board&) = 0;     // Return a move made by the player
    std::string str() const;                    // Return the string representation
};