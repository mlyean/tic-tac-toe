#include <iostream>

#include "client.hpp"
#include "players/human.hpp"

HumanPlayer::HumanPlayer(int id, Piece piece) : Player(id, piece) {}

HumanPlayer::HumanPlayer(int id, Piece piece, const std::string& name) : Player(id, piece, name) {}

HumanPlayer::~HumanPlayer() {}

Move HumanPlayer::getMove(const Board& board)
{
    std::pair<int, int> pos = TicTacToeClient::getHumanMove("[" + name + "] ");

    return {pos.first - 1, pos.second - 1, piece};
}