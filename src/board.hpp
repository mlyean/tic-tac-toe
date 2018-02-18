#pragma once

#include <array>
#include <string>

#include "move.hpp"
#include "piece.hpp"

class Board
{
    std::array<Piece, 9> board;

    void makeMove(Move);
    std::string str() const;
};