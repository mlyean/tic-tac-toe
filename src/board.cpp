#include <sstream>
#include <stdexcept>

#include "board.hpp"

Board::Board() {
    board.fill(Piece::EMPTY);
}

Board::~Board() {}

void Board::makeMove(Move move)
{
    board.at(move.i + 3 * move.j) = move.piece;
}

Piece Board::getPiece(int i, int j) const
{
    if (i < 0 || i >= 3) throw std::out_of_range("i out of range");
    if (j < 0 || j >= 3) throw std::out_of_range("j out of range");
    return getPiece(i + 3 * j);
}

Piece Board::getPiece(int pos) const
{
    return board.at(pos);
}

std::string Board::str() const
{
    std::ostringstream oss;
    for (int j = 0; j < 3; ++j)
    {
        for (int i = 0; i < 3; ++i)
        {
            oss << ' ' << static_cast<char>(getPiece(i, j)) << ' ';
            if (i != 2) oss << '|';
        }
        if (j != 2) oss << "\n---+---+---\n";
    }

    return oss.str();
}