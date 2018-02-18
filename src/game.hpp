#pragma once

#include <string>
#include <vector>

#include "board.hpp"
#include "move.hpp"
#include "player.hpp"

class Game
{
private:
    int turn;
    Player* player1;
    Player* player2;
    Board board;
    std::vector<Move> moveHistory;

public:
    enum class GameState
    {
        IN_PROGRESS,
        PLAYER_1_WIN,
        PLAYER_2_WIN,
        DRAW
    };

    Game(Player*, Player*);
    ~Game();
    GameState getState() const;
    void next();
    std::string str() const;
}