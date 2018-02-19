#include <iostream>

#include <ncurses.h>

#include "client.hpp"
#include "game.hpp"
#include "players/human.hpp"
#include "players/random.hpp"

std::string getStr()
{
    std::string input;
    
    nocbreak();
    echo();

    int ch = getch();

    while (ch != '\n')
    {
        input.push_back(ch);
        ch = getch();
    }

    cbreak();
    noecho();

    return input;
}

TicTacToeClient::TicTacToeClient() {}

TicTacToeClient::~TicTacToeClient() {}

void TicTacToeClient::promptName()
{
    printw("Player 1 Name: ");
    player1Name = getStr();
    printw("Player 2 Name: ");
    player2Name = getStr();
    printw("\n");
}

bool TicTacToeClient::promptRematch() const
{
    printw("Play again? [Y/n] ");
    echo();

    int response = getch();
    
    noecho();
    printw("\n");

    if (response == 'n' || response == 'N') return false;
    return true;
}

std::pair<int, int> TicTacToeClient::getHumanMove(std::string msg)
{
    int i = -1;
    int j = -1;

    printw(msg.c_str());

    printw("Row: ");

    while (i <= 0 || i > 3)
        i = getch() - '0';

    printw((std::to_string(i) + "\t").c_str());
    printw("Col: ");

    while (j <= 0 || j > 3)
        j = getch() - '0';
    
    printw((std::to_string(j) + "\n").c_str());
    
    return std::make_pair(i, j);
}

void TicTacToeClient::init()
{
    initscr();
    noecho();
    cbreak();

    printw("Welcome to Tic-Tac-Toe!\n");
    refresh();

    promptName();
}

void TicTacToeClient::run()
{
    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new HumanPlayer(2, Piece::CROSS, player2Name));

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            printw((game.board.str() + "\n\n").c_str());
            try { game.next(); }
            catch (std::exception &e) { printw("Invalid move detected, try again\n\n"); }
        }

        switch (game.getState()) {
        case Game::GameState::DRAW:
            printw("It's a draw!");
            break;
        case Game::GameState::PLAYER_1_WIN:
            printw((player1Name + " wins!").c_str());
            break;
        case Game::GameState::PLAYER_2_WIN:
            printw((player2Name + " wins!").c_str());
            break;
        default:
            break;
        }

        printw("\n\n");

        if (!promptRematch())
        {
            endwin();
            return;
        }
    }
}