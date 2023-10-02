#ifndef TAMEZX_MACRO_H
#define TAMEZX_MACRO_H

#include <cstdio>
#include <string>

enum class Key {
    None, Up, Down, Right, Left
};

const std::string Workspace = "/Users/shifathasan/Developer/C++/Tunneler";

#define TUNNELER printf("\033]50;SetProfile=Tunneler\a")
#define MainTerminal printf("\033]50;SetProfile=Terminal\a")

#define FLUSH fflush(stdout); fflush(stdin)

#define FRAME_ROWS 26
#define FRAME_COLS 60
// 1 / (0.1 seconds) = approximately 10 Frames per Second
#define FRAME_CYCLE (double)0.1

#define WINDOW_RESIZE(_H_, _W_) printf("\033[8;%d;%dt", (_H_), ((_W_) - 1))
#define SCREEN_CLEAR_ALL printf("\033[1;1H\033[2J\033[3J")

#define CURSOR_HIDE printf("\033[?25l")
#define CURSOR_SHOW printf("\033[?25h")
#define CURSOR_POSITION(_row_, _col_) printf("\033[%d;%dH", (_row_), (_col_))

#define RGBA_FG(_R_, _G_, _B_, _A_) printf("\033[38;2;%d;%d;%d;%dm", (_R_), (_G_), (_B_), (_A_))
#define RGBA_BG(_R_, _G_, _B_, _A_) printf("\033[48;2;%d;%d;%d;%dm", (_R_), (_G_), (_B_), (_A_))
#define RGBA_RESET printf("\033[m")

#endif //TAMEZX_MACRO_H








