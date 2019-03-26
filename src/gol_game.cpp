#include "gol_game.hpp"

#include <string>

using namespace gol;

Game::Game() {
    m_display.setWindowName("Conway's Game of Life");
    m_display.setRasterDimensions(178, 100);
    m_display.updateRasterDimensions();

    m_board.setAlive(50, 50);

    this->drawBoardToDisplay();
}
Game::~Game() {
}

void Game::refresh() {
    m_display.render();
}

void Game::drawBoardToDisplay() {
    Uint32* pixels;
    m_display.lock(&pixels);

    int width;
    int height;
    m_display.getRasterDimensions(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (m_board.isAlive(x, y)) {
                pixels[y*width + x] = m_aliveCell.toUint32();
            } else {
                pixels[y*width + x] = m_deadCell.toUint32();
            }
        }
    }

    m_display.unlock();
    m_display.render();
}
