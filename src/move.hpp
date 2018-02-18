#pragma once

#include "piece.hpp"

#include <string>

struct Move
{
    const int i;
    const int j;
    const Piece piece;

    Move(int, int, Piece);
    ~Move();
    std::string str() const;
};