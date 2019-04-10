#include "icu.hpp"

#include <iostream>

static void handleKeyEvent(SDL_Event &e) {
    switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
            state.quit = true;
            break;
        case SDLK_r:
            state.reset = true;
            break;
        // zoom
        case SDLK_k:
            state.zoom--;
            break;
        case SDLK_j:
            state.zoom++;
            break;
        // generation movement
        case SDLK_h:
            state.generationMovement = PREV_GEN;
            break;
        case SDLK_l:
            state.generationMovement = NEXT_GEN;
            break;
        // raster movement
        case SDLK_UP:
            state.y_pos++;
            break;
        case SDLK_LEFT:
            state.x_pos++;
            break;
        case SDLK_DOWN:
            state.y_pos--;
            break;
        case SDLK_RIGHT:
            state.x_pos--;
            break;
    }
}

static void handleEvent(SDL_Event &e) {
    switch (e.type) {
        case SDL_QUIT:
            state.quit = true;
            break;
        case SDL_KEYDOWN:
            handleKeyEvent(e);
            break;
    }
}

void handleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        handleEvent(e);
    }
}
