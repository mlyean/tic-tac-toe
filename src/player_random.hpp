#pragma once

#include <random>

#include "player.hpp"

struct RandomPlayer : public Player
{
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    RandomPlayer(int, Piece);                       // RandomPlayer constructor
    RandomPlayer(int, Piece, const std::string&);
    ~RandomPlayer();                                // RandomPlayer destructor
    virtual Move getMove(const Board&);             // Return a move made by RandomPlayer
};