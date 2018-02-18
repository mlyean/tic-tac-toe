#pragma once

#include "piece.hpp"

#include <string>

struct Move
{
    const int i;                // Column number
    const int j;                // Row number
    const Piece piece;          // Piece to use

    Move(int, int, Piece);      // Move constructor
    ~Move();                    // Move destructor
    std::string str() const;    // Return the string representation
};