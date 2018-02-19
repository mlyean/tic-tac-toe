#include <cctype>

#include <ncurses.h>

#include "client.hpp"
#include "game.hpp"
#include "players/human.hpp"
#include "players/random.hpp"

std::string getStr(WINDOW* win)
{
    std::string input;
    int ch;

    while (true) {
        ch = wgetch(win);

        if (ch == KEY_ENTER || ch == 10)
            return input;
        else if (ch == KEY_BACKSPACE || ch == 8)
        {
            if (input.length() > 0)
            {
                input.pop_back();
                int x, y;
                getyx(win, y, x);
                mvwaddch(win, y, x - 1, ' ');
                wmove(win, y, x - 1);
                wrefresh(win);
            }
        }
        else if (std::isprint(ch))
        {
            input.push_back(ch);
            waddch(win, ch);
        }
    }
}

TicTacToeClient::TicTacToeClient() {}

TicTacToeClient::~TicTacToeClient() {}

void TicTacToeClient::promptName()
{
    WINDOW* prompt(newwin(4, 48, 1, 1));
    box(prompt, 0, 0);

    mvwprintw(prompt, 1, 1, "Player 1 Name: ");
    player1Name = getStr(prompt);

    mvwprintw(prompt, 2, 1, "Player 2 Name: ");
    player2Name = getStr(prompt);

    wclear(prompt);
    wborder(prompt, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(prompt);
}

bool TicTacToeClient::promptRematch() const
{
    int ch;
    WINDOW* prompt(newwin(3, 48, 5, 1));
    box(prompt, 0, 0);

    mvwprintw(prompt, 1, 1, "Play again? [Y/n] ");
    ch = wgetch(prompt);

    wclear(prompt);
    wborder(prompt, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(prompt);
    
    if (ch == 'n' || ch == 'N') return false;

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
    
    printw((std::to_string(j) + "\n\n").c_str());
    
    return std::make_pair(i, j);
}

void TicTacToeClient::init()
{
    initscr();
    noecho();
    cbreak();

    printw("Welcome to Tic-Tac-Toe!\n\n");
    refresh();

    promptName();

    clear();
    move(0, 0);
}

void TicTacToeClient::run()
{
    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new RandomPlayer(2, Piece::CROSS, player2Name));

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            clear();
            printw((game.board.str() + "\n\n").c_str());
            game.next();
            refresh();
        }

        clear();
        move(1, 0);

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

        refresh();

        if (!promptRematch())
        {
            endwin();
            return;
        }
    }
}