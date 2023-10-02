#ifndef TUNNELER_TERMINAL_H
#define TUNNELER_TERMINAL_H

#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>

#include "macro.h"

static struct termios old_termios, new_termios;

class Terminal {
public:
    static void Set();

    static void Reset();
};

#endif //TUNNELER_TERMINAL_H



