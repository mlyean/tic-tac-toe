#pragma once

#include <array>
#include <string>

#include "game.hpp"
#include "move.hpp"
#include "piece.hpp"

class Board
{
private:
    std::array<Piece, 9> board;         // Internal tic-tac-toe board representation
    void makeMove(Move);                // Make a move and update the board
    friend void Game::next();           // Only allow Game::next to make a move

public:
    Board();                            // Board constructor
    ~Board();                           // Board destructor
    Piece getPiece(int, int) const;     // Return the piece located at given coordinates
    std::string str() const;            // Return the string representation
};