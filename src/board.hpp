#pragma once

#include <array>
#include <string>

#include "move.hpp"
#include "piece.hpp"

class Board
{
private:
    std::array<Piece, 9> board;         // Internal tic-tac-toe board representation
    void makeMove(Move);                // Make a move and update the board
    friend class Game;                  // Only allow Game::next to make a move

public:
    Board();                            // Board constructor
    ~Board();                           // Board destructor
    Piece getPiece(int, int) const;     // Return the piece located at given coordinates
    std::string str() const;            // Return the string representation
};