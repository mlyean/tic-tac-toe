#include <sstream>

#include "board.hpp"

Board::Board() {
    board.fill(Piece::EMPTY);
}

void Board::makeMove(const Move& move)
{
    board.at(move.i + 3 * move.j) = move.piece;
}

Piece Board::getPiece(int i, int j) const
{
    return board.at(i + 3 * j);
}

std::string Board::str() const
{
    std::ostringstream oss;
    for (int j = 0; j < 3; ++j)
    {
        for (int i = 0; i < 3; ++i)
        {
            oss << static_cast<char>(getPiece(i, j));
            if (i != 2) oss << ' ';
        }
        if (j != 2) oss << '\n';
    }

    return oss.str();
}