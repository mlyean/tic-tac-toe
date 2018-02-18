#include <iostream>

#include "game.hpp"
#include "player_human.hpp"
#include "player_random.hpp"

int main() {
    std::cout << "Welcome to Tic-Tac-Toe!\n";

    std::string player1Name, player2Name;
    std::cout << "What's your name Player 1? ";
    std::cin >> player1Name;
    player2Name = "Computer";

    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new RandomPlayer(2, Piece::CROSS, player2Name));

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            try { game.next(); }
            catch (std::exception &e) { std::cout << "Invalid move detected, try again\n"; }
        }

        std::cout << '\n';

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

        std::cout << std::endl;
    }

    return 0;
}