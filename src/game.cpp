#include <sstream>
#include <stdexcept>

#include "game.hpp"

const static int winPos[8][3] {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
};

Game::Game(Player* player1, Player* player2) : currPlayer(player1), nextPlayer(player2)
{
    turn = 1;
    moveHistory.reserve(9);
}

Game::~Game() {}

Game::GameState Game::getState() const
{
    if (turn > 9) return GameState::DRAW;

    for (int k = 0; k < 8; ++k) {
        Piece cmp = board.getPiece(winPos[k][0]);
        if (cmp == Piece::EMPTY) continue;
        if (board.getPiece(winPos[k][1]) != cmp) continue;
        if (board.getPiece(winPos[k][2]) != cmp) continue;
        
        if (turn % 2 == 0) return GameState::PLAYER_1_WIN;
        else return GameState::PLAYER_2_WIN;
    }

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