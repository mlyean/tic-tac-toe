#include <iostream>

#include "player_human.hpp"

HumanPlayer::HumanPlayer(int id, Piece piece) : Player(id, piece) {}

HumanPlayer::~HumanPlayer() {}

Move HumanPlayer::getMove(const Board& board)
{
    int i, j;
    std::cout << "Board state:\n" << board.str() << "\n\n[Player " << id << "] Move (row, col): ";
    std::cin >> j >> i;
    return {i + 1, j + 1, piece};
}