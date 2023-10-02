#include "Terminal.h"

void Terminal::Reset() {
    RGBA_RESET;
    CURSOR_POSITION(1, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    fflush(stdin);
    fflush(stdout);
    CURSOR_SHOW;
    SCREEN_CLEAR_ALL;
}

void Terminal::Set() {
    SCREEN_CLEAR_ALL;
    WINDOW_RESIZE(FRAME_ROWS, FRAME_COLS);
    tcgetattr(STDIN_FILENO, &old_termios);
    
    new_termios = old_termios; // save it to be able to Reset on exit

    new_termios.c_lflag &= ~(ICANON | ECHO); // set for non-canonical mode, no echo
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    CURSOR_HIDE;

    fflush(stdout);
}