#ifndef GOL_GAME_HPP
#define GOL_GAME_HPP

#include "brd_display.hpp"
#include "brd_pixel.hpp"
#include "gol_board.hpp"

namespace gol {

    class Game {
        public:
            Game();
            ~Game();

            void refresh();

        private:
            gol::Board m_board;
            brd::Display m_display;

            brd::Pixel m_aliveCell = brd::Pixel(0.0f, 0.0f, 0.0f);
            brd::Pixel m_deadCell = brd::Pixel(1.0f, 1.0f, 1.0f);

            void drawBoardToDisplay();
    };

}

#endif//GOL_GAME_HPP
