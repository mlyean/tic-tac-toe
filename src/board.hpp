#pragma once

#include <array>
#include <string>

#include "move.hpp"
#include "piece.hpp"

class Board
{
private:
    std::array<Piece, 9> board;

public:
    Board();
    ~Board();
    void makeMove(Move);
    Piece getPiece(int, int) const;
    std::string str() const;
};