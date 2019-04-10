#ifndef GOL_GAME_HPP
#define GOL_GAME_HPP

#include <vector>

#include "brd_display.hpp"
#include "brd_pixel.hpp"
#include "gol_board.hpp"

namespace gol {

    class Game {
        public:
            Game();
            ~Game();

            int setZoomLevel(int zoom);
            void setPosition(int x, int y);

            void nextGeneration();
            void prevGeneration();

            void refresh();

        private:
            std::vector<Board> m_generations;
            int m_currGenId = 0;
            int m_maxGenId = m_currGenId;
            brd::Display m_display;

            brd::Pixel m_aliveCell = brd::Pixel(0.0f, 0.0f, 0.0f);
            brd::Pixel m_deadCell = brd::Pixel(1.0f, 1.0f, 1.0f);

            int m_zoom = 0;
            int m_x_offset = 2;
            int m_y_offset = 5;

            void drawBoardToDisplay();
    };

}

#endif//GOL_GAME_HPP
