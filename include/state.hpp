#ifndef STATE_HPP
#define STATE_HPP

#include <string>

enum GenerationMovement{PREV_GEN, CURR_GEN, NEXT_GEN};

const std::string WINDOW_NAME  = "Conway's Game of Life";

struct State {
    bool reset = false;
    bool maxSpeed = false;
    bool quit = false;

    enum GenerationMovement generationMovement = CURR_GEN;

    int zoom = 1;
    int x_pos = 0;
    int y_pos = 0;
};

extern struct State state;

#endif
