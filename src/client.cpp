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
    int p1x, p2x, tmp;

    WINDOW* prompt(newwin(4, 48, 1, 1));
    box(prompt, 0, 0);

    mvwprintw(prompt, 1, 1, "Player 1 Name: ");
    getyx(prompt, tmp, p1x);
    mvwprintw(prompt, 2, 1, "Player 2 Name: ");
    getyx(prompt, tmp, p2x);

    wattron(prompt, A_BOLD);

    wmove(prompt, 1, p1x);
    player1Name = getStr(prompt);
    wmove(prompt, 2, p2x);
    player2Name = getStr(prompt);

    wattroff(prompt, A_BOLD);

    wclear(prompt);
    wborder(prompt, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(prompt);
}

bool TicTacToeClient::promptRematch() const
{

    int ch, x, tmp;
    WINDOW* prompt(newwin(1, COLS, LINES - 1, 1));

    wattrset(prompt, A_REVERSE);
    mvwprintw(prompt, 0, 1, "Play again? [y/n] ");
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

    WINDOW* prompt(newwin(1, COLS, LINES - 1, 1));

    wattrset(prompt, A_REVERSE);

    mvwprintw(prompt, 0, 1, msg.c_str());

    wprintw(prompt, "Row: ");
    getyx(prompt, tmp, rowx);
    waddch(prompt, '\t');
    wprintw(prompt, "Col: ");
    getyx(prompt, tmp, colx);
    waddch(prompt, '\t');    

    wmove(prompt, 0, rowx);
    while (i <= 0 || i > 3)
        i = wgetch(prompt) - '0';
    
    waddch(prompt, i + '0');

    wmove(prompt, 0, colx);
    while (j <= 0 || j > 3)
        j = wgetch(prompt) - '0';
    
    waddch(prompt, j + '0');

    wclear(prompt);
    wrefresh(prompt);
    
    return std::make_pair(i, j);
}

void TicTacToeClient::init()
{
    initscr();
    noecho();
    cbreak();

    printw("Tic-Tac-Toe\n\n");
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
            mvprintw(1, 0, (game.board.str() + "\n\n").c_str());
            refresh();
            game.next();
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