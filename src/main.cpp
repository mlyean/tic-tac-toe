#include <iostream>

#include "game.hpp"
#include "player_human.hpp"

int main() {
    std::cout << "Welcome to Tic-Tac-Toe!\n\n";

    Game game(new HumanPlayer(1, Piece::KNOT), new HumanPlayer(2, Piece::CROSS));

    while (game.getState() == Game::GameState::IN_PROGRESS)
    {
        try {
            game.next();
        }
        catch (std::exception &e) {}
    }
    
    return 0;
}