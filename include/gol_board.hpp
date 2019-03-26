/** game of life - game board
 * This game board keeps track of all Cell data, where they are and whether they
 * are alive or not. There are no boundaries and cells are dynamically allocated
 * by which this board can practically be considered infinite.
 * Currently it is implemented for 2-dimensional boards only and not optimised
 * for performance, but the general abstraction is meant to easily improve those
 * aspects.
 */
#ifndef GOL_BOARD_HPP
#define GOL_BOARD_HPP

#include <vector>

namespace gol {

    class Board {
        public:
            Board();
            ~Board();

            bool isAlive(int x, int y);
            bool isDead(int x, int y);

            void setAlive(int x, int y);
            void setDead(int x, int y);

        private:
            struct Cell {
                    int x;
                    int y;
                    bool isAlive = true;
            };

            std::vector<Cell> m_cells;

            Cell* findCell(int x, int y);
            void insertCell(int x, int y, bool isAlive);

            void setCellStatus(int x, int y, int isAlive);
    };

}

#endif//GOL_BOARD_HPP
