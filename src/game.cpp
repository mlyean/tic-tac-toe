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
    if (turn > 9) return GameState::DRAW;

    bool hasWinner = false;
    
    // Check columns
    for (int i = 0; i < 3; ++i)
    {
        Piece cmp = board.getPiece(i, 0);
        if (cmp == Piece::EMPTY) continue;
        if (board.getPiece(i, 1) != cmp) continue;
        if (board.getPiece(i, 2) != cmp) continue;
        // Column found
        hasWinner = true;
    }

    // Check rows
    for (int j = 0; j < 3; ++j)
    {
        Piece cmp = board.getPiece(0, j);
        if (cmp == Piece::EMPTY) continue;
        if (board.getPiece(1, j) != cmp) continue;
        if (board.getPiece(2, j) != cmp) continue;
        // Row found
        hasWinner = true;
    }

    // Check diagonals
    {
        Piece cmp = board.getPiece(0, 0);
        if (cmp != Piece::EMPTY)
            if (board.getPiece(1, 1) == cmp)
                if (board.getPiece(2, 2) == cmp)
                    hasWinner = true;
    }

    {
        Piece cmp = board.getPiece(2, 0);
        if (cmp != Piece::EMPTY)
            if (board.getPiece(1, 1) == cmp)
                if (board.getPiece(0, 2) == cmp)
                    hasWinner = true;
    }

    if (hasWinner)
    {
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