#pragma once

#include <sstream>
#include <stdexcept>

#include "game.hpp"

Game::Game(Player* player1, Player* player2) : player1(player1), player2(player2)
{
    turn = 1;
    moveHistory.reserve(9);
}

Game::~Game()
{
    delete player1;
    delete player2;
}

Game::GameState Game::getState() const
{
    if (turn == 10) return GameState::DRAW;
    // Stub
    return GameState::DRAW;
}

void Game::next()
{
    if (turn > 9) throw std::out_of_range("Number of turns exceeded");
    
    Player* currentPlayer;
    if (turn % 2 == 1) currentPlayer = player1;
    else currentPlayer = player2;

    Move mv = currentPlayer->getMove(board);

    if (board.getPiece(mv.i, mv.j) != Piece::EMPTY) {
        std::ostringstream oss;
        oss << "Player " << currentPlayer->id << " attempted to overwrite move";
        throw std::invalid_argument(oss.str());
    }

    if (mv.piece != currentPlayer->piece) {
        std::ostringstream oss;
        oss << "Player " << currentPlayer->id << " attempted to use false piece";
        throw std::invalid_argument(oss.str());
    }
    
    board.makeMove(mv);
    
    turn++;

    delete currentPlayer;
}

std::string Game::str() const
{
    std::ostringstream oss;
    oss << "{ player1: " << player1->str() << ", player2: " << player2->str() << ", turn: " << turn << " }";
    return oss.str();
}