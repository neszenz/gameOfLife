#include "gol_board.hpp"

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
}

void Board::setCellStatus(int x, int y, int isAlive) {
    Board::Cell* existing_cell = this->findCell(x, y);
    if (existing_cell != nullptr) {
        existing_cell->isAlive = isAlive;
    } else {
        this->insertCell(x, y, isAlive);
    }
}
