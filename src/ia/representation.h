#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include "global.h"
#include "robot.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;


std::vector<int> setupWall(int w, int h);
std::vector<int> setupWallVisited(int w, int h);



struct repr {
        // wall representation
        std::vector<int> wall;

        //Visited
        std::vector<int>visited;

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
        repr(unsigned int w, unsigned int h) : wall(setupWall(w,h)), visited(setupWallVisited(w,h)),adjmatrix(w,h){}

}; // end of repr

int getIndexWallVisited(int row,int col);

int getIndexAdj(int row,int col);
void completement_ad_information (Robot robot, repr *reper, int nb_case, bool inverse);
void wall_visited (Robot robot, repr *reper, int nb_case);
void ad_information (Robot robot, int distance, repr *reper);

#endif // REPRESENTATION_H
