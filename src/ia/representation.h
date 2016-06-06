#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include "global.h"
//Struct Cell
struct Cell{
    int dist; //Distance to other cell
    int dir;    //Direction to take
};

//Struct Repr
struct repr{

    //Matrice des murs
    int wall[SIZE_X*SIZE_Y];

    //Matrice adj
    Cell adjmatrix[SIZE_X*SIZE_Y][SIZE_X*SIZE_Y];
};

#endif // REPRESENTATION_H
