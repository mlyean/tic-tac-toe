#include <ncurses.h>

#include "client.hpp"
#include "game.hpp"
#include "players/human.hpp"
#include "players/random.hpp"
#include "util.hpp"

TicTacToeClient::TicTacToeClient() {}

TicTacToeClient::~TicTacToeClient() {}

void TicTacToeClient::promptName()
{
    int p1x, p2x, tmp;

    WINDOW* prompt(newwin(4, 48, 2, 2));
    box(prompt, 0, 0);

    mvwprintw(prompt, 1, 1, "Player 1 Name: ");
    getyx(prompt, tmp, p1x);
    mvwprintw(prompt, 2, 1, "Player 2 Name: ");
    getyx(prompt, tmp, p2x);

    wattron(prompt, A_BOLD);

    wmove(prompt, 1, p1x);
    player1Name = getStr(prompt, 20);
    wmove(prompt, 2, p2x);
    player2Name = getStr(prompt, 20);

    wattroff(prompt, A_BOLD);

    wclear(prompt);
    wrefresh(prompt);
}

bool TicTacToeClient::promptRematch() const
{
    int ch, x, tmp;

    WINDOW* prompt(statusBar());
    wprintw(prompt, "Play again? [y/n] ");
    getyx(prompt, tmp, x);
    waddch(prompt, '\t');
    wmove(prompt, 0, x);

    wrefresh(prompt);

    while (true) {
        ch = wgetch(prompt);

        switch (ch) {
        case 'n':
        case 'N':
            wclear(prompt);
            wrefresh(prompt);
            return false;
        case 10:
        case KEY_ENTER:
        case 'y':
        case 'Y':
            wclear(prompt);
            wrefresh(prompt);
            return true;
        default:
            continue;
        }
    }
}

std::pair<int, int> TicTacToeClient::getHumanMove(std::string msg)
{
    int i = 0;
    int j = 0;

    int rowx, colx, tmp;

    WINDOW* prompt(statusBar());
    wprintw(prompt, msg.c_str());

    wprintw(prompt, "Row: ");
    getyx(prompt, tmp, rowx);
    waddch(prompt, '\t');
    wprintw(prompt, "Col: ");
    getyx(prompt, tmp, colx);
    waddch(prompt, '\t');    

    wmove(prompt, 0, rowx);
    while (j <= 0 || j > 3)
        j = wgetch(prompt) - '0';
    
    waddch(prompt, j + '0');

    wmove(prompt, 0, colx);
    while (i <= 0 || i > 3)
        i = wgetch(prompt) - '0';
    
    waddch(prompt, i + '0');

    wclear(prompt);
    wrefresh(prompt);
    
    return std::make_pair(i, j);
}

void TicTacToeClient::init()
{
    initscr();
    noecho();
    cbreak();

    if (has_colors())
        start_color();
    
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    WINDOW* titlebar(newwin(1, 20, 0, 0));
    wattrset(titlebar, A_BOLD);
    wprintw(titlebar, "Tic-Tac-Toe");
    wrefresh(titlebar);

    promptName();
}

void TicTacToeClient::run()
{
    while (true)
    {
        Game game(new HumanPlayer(1, Piece::KNOT, player1Name), new RandomPlayer(2, Piece::CROSS, player2Name));

        WINDOW* boardBox(newwin(7, 13, 2, 2));
        box(boardBox, 0, 0);

        while (game.getState() == Game::GameState::IN_PROGRESS)
        {
            drawBoard(boardBox, game.board);
            game.next();
        }

        wclear(boardBox);
        wrefresh(boardBox);

        std::string res;

        if (game.getState() == Game::GameState::DRAW)
            res = "It's a draw!";
        else if (game.getState() == Game::GameState::PLAYER_1_WIN)
            res = player1Name + " wins!";
        else if (game.getState() == Game::GameState::PLAYER_2_WIN)
            res = player2Name + " wins!";

        WINDOW* result(resultWin(res));

        if (!promptRematch())
        {
            endwin();
            return;
        }

        wclear(result);
        wrefresh(result);
    }
}