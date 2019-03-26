#include "gol_game.hpp"

#include <iostream>
#include <string>

#define DEFAULT_ZOOM_LEVEL 10

using namespace gol;

Game::Game() {
    m_display.setWindowName("Conway's Game of Life");
    m_display.showMetaCounter(true);

    m_board.setAlive(-1, 0);
    m_board.setAlive(0, 0);
    m_board.setAlive(1, 0);

    m_board.setAlive(-10, -10);
    m_board.setAlive(10, -10);
    m_board.setAlive(-10, 10);
    m_board.setAlive(10, 10);
}
Game::~Game() {
}

int Game::setZoomLevel(int zoom) {
    m_zoom = (zoom > -DEFAULT_ZOOM_LEVEL)? zoom : -DEFAULT_ZOOM_LEVEL+1;
    return m_zoom;
}
void Game::setPosition(int x, int y) {
    m_x_offset = x;
    m_y_offset = y;
}

void Game::playOneRound() {
    m_board.computeNextGeneration();
}

void Game::refresh() {
    // texture dimensions need to fit aspect ratio of the display and zoom
    int y = DEFAULT_ZOOM_LEVEL + m_zoom;
    float aspect = m_display.getAspectRatio();

    // using odd dimensions to always have one center cell
    int odd_x = 2 * int(y*aspect) + 1;
    int odd_y = 2 * y + 1;

    m_display.setRasterDimensions(odd_x, odd_y);
    m_display.updateRasterDimensions();

    this->drawBoardToDisplay();

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
            // map board origin to texture center
            int x_board = (width / 2) + m_x_offset;
            int y_board = (height / 2) + m_y_offset;

            if (m_board.isAlive(x - x_board, y - y_board)) {
                pixels[y * width + x] = m_aliveCell.toUint32();
            } else {
                pixels[y * width + x] = m_deadCell.toUint32();
            }
        }
    }

    m_display.unlock();
    m_display.render();
}
