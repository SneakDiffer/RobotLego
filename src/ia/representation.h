#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include "global.h"
#include <vector>

struct repr {

        // wall representation
        std::vector<int> wall;

        //Visited
        std::vector<bool>visited;
        // cell
        struct cell {
                int dir;
                int dist;
                cell() : dir(0), dist(-1) {}
        };

        // adjacency and direction matrix
        struct adjmat_s {
                std::vector<cell> mat;
                adjmat_s(unsigned int w, unsigned h) : mat(w*w*h*h) {}
        } adjmatrix;

        // constructor
        repr(unsigned int w, unsigned int h) : wall(w*h), visited(w*h,false),adjmatrix(w,h){}

}; // end of repr


#endif // REPRESENTATION_H
