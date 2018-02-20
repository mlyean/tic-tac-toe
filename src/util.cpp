#include "util.hpp"

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

WINDOW* resultWin(std::string str)
{
    WINDOW* result(newwin(3, 30, 1, 1));
    box(result, 0, 0);
    mvwprintw(result, 1, 1, str.c_str());
    wrefresh(result);
}

void drawBoard(WINDOW* boardBox, Board board)
{
    for (int j = 0; j < 3; ++j)
    {
        wmove(boardBox, 2 * j + 1, 1);
        for (int i = 0; i < 3; ++i)
        {
            waddch(boardBox, ' ');

            switch (board.getPiece(i, j))
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
}
