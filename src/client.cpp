#include <cctype>

#include <ncurses.h>

#include "client.hpp"
#include "game.hpp"
#include "players/human.hpp"
#include "players/random.hpp"

std::string getStr(WINDOW* win, int width)
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
        else if (std::isprint(ch) && input.size() < width)
        {
            input.push_back(ch);
            waddch(win, ch);
        }
    }
}

WINDOW* statusBar()
{
    WINDOW* status(newwin(1, COLS, LINES - 1, 1));
    wattrset(status, A_REVERSE);
    wmove(status, 0, 1);
    return status;
}

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
            for (int j = 0; j < 3; ++j)
            {
                wmove(boardBox, 2 * j + 1, 1);
                for (int i = 0; i < 3; ++i)
                {
                    waddch(boardBox, ' ');

                    switch (game.board.getPiece(i, j))
                    {
                    case Piece::KNOT:
                        waddch(boardBox, 'O' | A_BOLD | COLOR_PAIR(1));
                        break;
                    case Piece::CROSS:
                        waddch(boardBox, 'X' | A_BOLD | COLOR_PAIR(2));
                        break;
                    default:
                        waddch(boardBox, ' ');
                    }

                    waddch(boardBox, ' ');
                    if (i < 2)
                        waddch(boardBox, ACS_VLINE);
                }
                if (j < 2)
                {
                    wmove(boardBox, 2 * j + 2, 1);
                    for (int k = 0; k < 3; ++k)
                    {
                        waddch(boardBox, ACS_HLINE);
                        waddch(boardBox, ACS_HLINE);
                        waddch(boardBox, ACS_HLINE);
                        if (k < 2)
                            waddch(boardBox, ACS_PLUS);
                    }
                }
            }
            wrefresh(boardBox);
            game.next();
        }

        wclear(boardBox);
        wrefresh(boardBox);

        WINDOW* result(newwin(3, 30, 1, 1));
        box(result, 0, 0);
        wmove(result, 1, 1);

        switch (game.getState()) {
        case Game::GameState::DRAW:
            wprintw(result, "It's a draw!");
            break;
        case Game::GameState::PLAYER_1_WIN:
            wprintw(result, (player1Name + " wins!").c_str());
            break;
        case Game::GameState::PLAYER_2_WIN:
            wprintw(result, (player2Name + " wins!").c_str());
            break;
        default:
            break;
        }
        wrefresh(result);

        if (!promptRematch())
        {
            endwin();
            return;
        }

        wclear(result);
        wrefresh(result);
    }
}