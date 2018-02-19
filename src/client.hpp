#pragma once

#include <string>

class TicTacToeClient
{
private:
    std::string player1Name;
    std::string player2Name;
    void promptName();
    bool promptRematch() const;

public:
    TicTacToeClient();
    ~TicTacToeClient();
    void init();
    void run();
};