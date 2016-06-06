#include "grid.h"


Grid::Grid(unsigned int w, unsigned int h, Cell val)
        : _grid(h, std::vector<Cell>(w, val))
        , _h(h)
        , _w(w)
{
}

Grid::~Grid() {}


Cell Grid::operator() (unsigned int x, unsigned int y) {
        if ((x < _w) && (y < _h))
                return _grid[y][x];
        else
                return {0,0};
}
