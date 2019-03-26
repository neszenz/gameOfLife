#ifndef STATE_HPP
#define STATE_HPP

#include <string>

const std::string WINDOW_NAME  = "Conway's Game of Life";

struct State {
    bool quit = false;
    bool update = true;
    int zoom = 0;
};

extern struct State state;

#endif
