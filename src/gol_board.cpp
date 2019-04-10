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

int Board::numOfAliveNeighbors(int x, int y) {
    int numOfAliveNeighbors = 0;

    // top row
    numOfAliveNeighbors += (this->isAlive(x - 1, y + 1))? 1 : 0;
    numOfAliveNeighbors += (this->isAlive(x + 0, y + 1))? 1 : 0;
    numOfAliveNeighbors += (this->isAlive(x + 1, y + 1))? 1 : 0;
    // left and right
    numOfAliveNeighbors += (this->isAlive(x - 1, y + 0))? 1 : 0;
    numOfAliveNeighbors += (this->isAlive(x + 1, y + 0))? 1 : 0;
    // bottom row
    numOfAliveNeighbors += (this->isAlive(x - 1, y - 1))? 1 : 0;
    numOfAliveNeighbors += (this->isAlive(x + 0, y - 1))? 1 : 0;
    numOfAliveNeighbors += (this->isAlive(x + 1, y - 1))? 1 : 0;

    return numOfAliveNeighbors;
}

Board Board::computeNextGeneration() {
    Board nextGenBoard;

    // iterate over all cells, 1st check if it dies, 2nd if neighbore is revived
    for (Board::Cell cell : m_cells) {
        // dead cells can be omitted
        if (cell.isAlive == false) {
            continue;
        }

        // count alive neighbor cells and eventually set cell alive in next gen
        int aliveNeighbors = this->numOfAliveNeighbors(cell.x, cell.y);
        if (aliveNeighbors >= 2 && aliveNeighbors <= 3) {
            nextGenBoard.setAlive(cell.x, cell.y);
        }

        // revive neighbor cell if is has 3 alive neighbors
        for (int iY = cell.y-1; iY <= cell.y+1; iY++) {
            for (int iX = cell.x-1; iX <= cell.x+1; iX++) {
                if (iY == 0 && iX == 0) {
                    continue;
                }

                if (this->numOfAliveNeighbors(iX, iY) == 3) {
                    nextGenBoard.setAlive(iX, iY);
                }
            }
        }
    }

    return nextGenBoard;
}
