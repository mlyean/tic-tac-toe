#include <iostream>

#include "game.hpp"
#include "player_human.hpp"

int main() {
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    std::string player1Name, player2Name;
    std::cout << "What's your name Player 1? ";
    std::cin >> player1Name;
    std::cout << "What's your name Player 2? ";
    std::cin >> player2Name;

    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new HumanPlayer(2, Piece::CROSS, player2Name));

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            try { game.next(); }
            catch (std::exception &e) { std::cout << "Invalid move detected, try again\n"; }
        }

        switch (game.getState()) {
        case Game::GameState::DRAW:
            std::cout << "\nIt's a draw!\n";
            break;
        case Game::GameState::PLAYER_1_WIN:
            std::cout << "\n" << player1Name << " wins!\n";
            break;
        case Game::GameState::PLAYER_2_WIN:
            std::cout << "\n" << player2Name << " wins!\n";
            break;
        default:
            break;
        }
    }

    return 0;
}