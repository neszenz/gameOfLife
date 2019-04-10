#include "gol_game.hpp"

#include <iostream>
#include <string>

#define DEFAULT_ZOOM_LEVEL 10

using namespace gol;

Game::Game() {
    m_display.setWindowName("Conway's Game of Life");
    m_display.showMetaCounter(true);

    // create initial generation
    m_generations.emplace_back(Board());

    // glider 1
    m_generations.back().setAlive(-5, -4);
    m_generations.back().setAlive(-4, -3);
    m_generations.back().setAlive(-3, -3);
    m_generations.back().setAlive(-3, -4);
    m_generations.back().setAlive(-3, -5);
    // glider 2
    m_generations.back().setAlive(5, -4);
    m_generations.back().setAlive(4, -3);
    m_generations.back().setAlive(3, -3);
    m_generations.back().setAlive(3, -4);
    m_generations.back().setAlive(3, -5);
    // glider 3
    m_generations.back().setAlive(-5, 4);
    m_generations.back().setAlive(-4, 3);
    m_generations.back().setAlive(-3, 3);
    m_generations.back().setAlive(-3, 4);
    m_generations.back().setAlive(-3, 5);
    // glider 4
    m_generations.back().setAlive(5, 4);
    m_generations.back().setAlive(4, 3);
    m_generations.back().setAlive(3, 3);
    m_generations.back().setAlive(3, 4);
    m_generations.back().setAlive(3, 5);

    // line 1
    m_generations.back().setAlive(-1, -10);
    m_generations.back().setAlive(0, -10);
    m_generations.back().setAlive(1, -10);
    // line 2
    m_generations.back().setAlive(-10, 1);
    m_generations.back().setAlive(-10, 0);
    m_generations.back().setAlive(-10, -1);
    // line 3
    m_generations.back().setAlive(10, 1);
    m_generations.back().setAlive(10, 0);
    m_generations.back().setAlive(10, -1);
    // line 4
    m_generations.back().setAlive(-1, 10);
    m_generations.back().setAlive(0, 10);
    m_generations.back().setAlive(1, 10);

    // reference points
    m_generations.back().setAlive(-10, -10);
    m_generations.back().setAlive(10, -10);
    m_generations.back().setAlive(-10, 10);
    m_generations.back().setAlive(10, 10);
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

void Game::nextGeneration() {
    if (m_currGenId + 1 <= m_maxGenId) {
        m_currGenId++;
        return;
    }

    m_generations.emplace_back(m_generations.at(m_currGenId).computeNextGeneration());
    m_currGenId++;
    m_maxGenId++;
}

void Game::prevGeneration() {
    if (m_currGenId - 1 >= 0) {
        m_currGenId--;
    }
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
    std::string windowName = "Conway's Game of Life (" + ToString(m_currGenId) + ") ";
    m_display.setWindowName(windowName);

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

            if (m_generations.at(m_currGenId).isAlive(x - x_board, y - y_board)) {
                pixels[y * width + x] = m_aliveCell.toUint32();
            } else {
                pixels[y * width + x] = m_deadCell.toUint32();
            }
        }
    }

    m_display.unlock();
    m_display.render();
}
