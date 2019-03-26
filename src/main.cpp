#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "brd_display.hpp"
#include "brd_pixel.hpp"
#include "brd_util.hpp"
#include "gol_game.hpp"
#include "icu.hpp"
#include "state.hpp"

// global engine state
struct State state;

int main(int argc, const char* argv[]) {
    // must be done to use brd::Display
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        logSDLError(std::cerr, "SDL_Init()");
        SDL_Quit();
        return 1;
    }

    gol::Game game;

    while(!state.quit) {
        handleEvents();

        // gets assigned the return value b/ zoom can hit a limit
        state.zoom = game.setZoomLevel(state.zoom);

        game.refresh();
    }

    SDL_Quit();
    return 0;
}
