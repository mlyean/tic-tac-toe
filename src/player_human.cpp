#include <iostream>

#include "player_human.hpp"

HumanPlayer::HumanPlayer(int id, Piece piece) : Player(id, piece) {}

HumanPlayer::HumanPlayer(int id, Piece piece, const std::string& name) : Player(id, piece, name) {}

HumanPlayer::~HumanPlayer() {}

Move HumanPlayer::getMove(const Board& board)
{
    int i, j;
    std::cout << '[' << name << "] Move (row, col): ";
    std::cin >> j >> i;
    std::cout << '\n';

    return {i - 1, j - 1, piece};
}