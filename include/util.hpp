#pragma once

#include <cctype>
#include <string>

#include <ncurses.h>

#include "board.hpp"

std::string getStr(WINDOW* win, int width);

WINDOW* statusBar();

WINDOW* resultWin(std::string str);

void drawBoard(WINDOW* boardBox, Board board);