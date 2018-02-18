#pragma once

#include <array>
#include <string>

#include "game.hpp"
#include "move.hpp"
#include "piece.hpp"

class Board
{
private:
    std::array<Piece, 9> board;
    void makeMove(Move);
    friend void Game::next();

public:
    Board();
    ~Board();
    Piece getPiece(int, int) const;
    std::string str() const;
};