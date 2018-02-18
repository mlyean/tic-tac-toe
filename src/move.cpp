#include <sstream>
#include <stdexcept>
#include <string>

#include "move.hpp"

Move::Move(int i, int j, Piece piece) : i(i), j(j), piece(piece)
{
    if (i < 0 || i >= 3) throw std::invalid_argument("i out of range");
    if (j < 0 || j >= 3) throw std::invalid_argument("j out of range");
    if (piece == Piece::EMPTY) throw std::invalid_argument("Argument piece is EMPTY");
}

std::string Move::str() const
{
    std::ostringstream oss;
    oss << "{ i: " << i << ", j: " << j << ", piece: " << static_cast<char>(piece) << " }";
    return oss.str();
}