#include <sstream>
#include <stdexcept>

#include "game.hpp"

Game::Game(Player* player1, Player* player2) : currPlayer(player1), nextPlayer(player2)
{
    turn = 1;
    moveHistory.reserve(9);
}

Game::~Game() {}

Game::GameState Game::getState() const
{
    if (turn == 10) return GameState::DRAW;
    // Stub
    return GameState::IN_PROGRESS;
}

void Game::next()
{
    if (turn > 9) throw std::out_of_range("Number of turns exceeded");

    Move mv = currPlayer->getMove(board);

    if (board.getPiece(mv.i, mv.j) != Piece::EMPTY) {
        std::ostringstream oss;
        oss << "Player " << currPlayer->id << " attempted to overwrite move";
        throw std::invalid_argument(oss.str());
    }

    if (mv.piece != currPlayer->piece) {
        std::ostringstream oss;
        oss << "Player " << currPlayer->id << " attempted to use false piece";
        throw std::invalid_argument(oss.str());
    }
    
    board.makeMove(mv);
    moveHistory.push_back(mv);
    currPlayer.swap(nextPlayer);
    
    turn++;
}

std::string Game::str() const
{
    std::ostringstream oss;
    oss << "{ currPlayer: " << currPlayer->str() << ", nextPlayer: " << nextPlayer->str() << ", turn: " << turn << " }";
    return oss.str();
}