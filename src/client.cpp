#include <iostream>

#include "client.hpp"
#include "game.hpp"
#include "players/human.hpp"
#include "players/random.hpp"

TicTacToeClient::TicTacToeClient() {}

TicTacToeClient::~TicTacToeClient() {}

void TicTacToeClient::promptName()
{
    std::cout << "Player 1 Name: ";
    std::cin >> player1Name;
    std::cout << "Player 2 Name: ";
    std::cin >> player2Name;
    std::cout << '\n';
}

bool TicTacToeClient::promptRematch() const
{
    char response;
    std::cout << "Play again? [Y/n] ";
    std::cin >> response;
    std::cout << '\n';

    if (response == 'n' || response == 'N') return false;
    return true;
}

void TicTacToeClient::init()
{
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    promptName();
}

void TicTacToeClient::run()
{
    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new HumanPlayer(2, Piece::CROSS, player2Name));

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            std::cout << game.board.str() << "\n\n";
            try { game.next(); }
            catch (std::exception &e) { std::cout << "Invalid move detected, try again\n\n"; }
        }

        switch (game.getState()) {
        case Game::GameState::DRAW:
            std::cout << "It's a draw!";
            break;
        case Game::GameState::PLAYER_1_WIN:
            std::cout << player1Name << " wins!";
            break;
        case Game::GameState::PLAYER_2_WIN:
            std::cout << player2Name << " wins!";
            break;
        default:
            break;
        }

        std::cout << "\n\n";

        if (!promptRematch()) return;
    }
}