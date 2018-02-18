#pragma once

#include <string>
#include <vector>

#include "board.hpp"
#include "move.hpp"
#include "player.hpp"

class Game
{
private:
    int turn;                       // Turn number
    Player* player1;                // Pointer to first player
    Player* player2;                // Pointer to second player
    Board board;                    // Game board
    std::vector<Move> moveHistory;  // History of moves from first to last

public:
    enum class GameState
    {
        IN_PROGRESS,                // The game is in progress
        PLAYER_1_WIN,               // Player 1 wins the game
        PLAYER_2_WIN,               // Player 2 wins the game
        DRAW                        // The game ends in a draw
    };

    Game(Player*, Player*);         // Game constructor
    ~Game();                        // Game destructor
    GameState getState() const;     // Return the state of the game
    void next();                    // Get move from the player and excecute the move
    std::string str() const;        // Return the string representation
}