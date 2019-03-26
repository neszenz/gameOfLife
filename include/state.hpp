#ifndef STATE_HPP
#define STATE_HPP

#include <string>

const std::string WINDOW_NAME  = "Conway's Game of Life";

struct State {
    bool quit = false;
    bool play = false;
    bool reset = false;

    int zoom = 1;
    int x_pos = 0;
    int y_pos = 0;
};

extern struct State state;

#endif
