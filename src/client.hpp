#pragma once

#include <string>

class TicTacToeClient
{
private:
    std::string player1Name;        // Name of player 1
    std::string player2Name;        // Name of player 2
    void promptName();              // Prompt to get player names
    bool promptRematch() const;     // Prompt to rematch

public:
    TicTacToeClient();              // TicTacToeClient constructor
    ~TicTacToeClient();             // TicTacToeClient destructor
    void init();                    // Print greetings and prompt for names
    void run();                     // Start game loop
};