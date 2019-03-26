#include "gol_board.hpp"

#include <iostream>

using namespace gol;

Board::Board() {
}

Board::~Board() {
}

bool Board::isAlive(int x, int y) {
    Cell* cell = this->findCell(x, y);
    if (cell != nullptr) {
        return cell->isAlive;
    }

    return false;
}
bool Board::isDead(int x, int y) {
    return !(this->isAlive(x, y));
}

void Board::setAlive(int x, int y) {
    this->setCellStatus(x, y, true);
}
void Board::setDead(int x, int y) {
    this->setCellStatus(x, y, false);
}

Board::Cell* Board::findCell(int x, int y) {
    for (Board::Cell& cell : m_cells) {
        if (cell.x == x && cell.y == y) {
            return &cell;
        }
    }

    return nullptr;
}
void Board::insertCell(int x, int y, bool isAlive) {
    m_cells.emplace_back(Board::Cell({.x = x, .y = y, .isAlive = isAlive}));

    // update bounding box
    m_boundingBox.x_min = (x < m_boundingBox.x_min)? x : m_boundingBox.x_min;
    m_boundingBox.x_max = (x > m_boundingBox.x_max)? x : m_boundingBox.x_max;
    m_boundingBox.y_min = (y < m_boundingBox.y_min)? y : m_boundingBox.y_min;
    m_boundingBox.y_max = (y > m_boundingBox.y_max)? y : m_boundingBox.y_max;
}

void Board::setCellStatus(int x, int y, int isAlive) {
    Board::Cell* existing_cell = this->findCell(x, y);
    if (existing_cell != nullptr) {
        existing_cell->isAlive = isAlive;
    } else {
        this->insertCell(x, y, isAlive);
    }
}

void Board::computeNextGeneration() {
    std::cout << "next gen" << std::endl;
}
