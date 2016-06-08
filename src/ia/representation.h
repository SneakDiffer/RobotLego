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

int getIndexWallVisited(int row,int col){
    //On vérifie qu'on est bien dans le tableau
    if(row < conf::SIZE_X && col < conf::SIZE_Y){
        return (conf::SIZE_Y*row)+col;
    }else{
        return -1;
    }
}

int getIndexAdj(int row,int col){
    //On vérifie qu'on est bien dans le tableau
    if(row < conf::SIZE_X*conf::SIZE_Y && col < conf::SIZE_X*conf::SIZE_Y){
        return ((conf::SIZE_Y*conf::SIZE_X)*row)+col;
    }else{
        return -1;
    }
}

#endif // REPRESENTATION_H
