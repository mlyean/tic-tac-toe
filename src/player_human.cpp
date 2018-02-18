#include <iostream>

#include "player_human.hpp"

HumanPlayer::HumanPlayer(int id, Piece piece) : Player(id, piece) {}

Move HumanPlayer::getMove(const Board& board)
{
    int i, j;
    std::cout << "Board state:\n" << board.str() << "\nYour move?";
    std::cin >> i >> j;
    return {i, j, piece};
}