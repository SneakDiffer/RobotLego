#ifndef GRID_H
#define GRID_H

#include <vector>

#include "representation.h"

class Grid {
public:
        Grid(unsigned int w, unsigned int h, Cell val);
        ~Grid();

        Cell operator()(unsigned int x, unsigned int y);
private:
        std::vector<std::vector<Cell>> _grid;
        unsigned int _h, _w;
};

#endif // GRID_H
