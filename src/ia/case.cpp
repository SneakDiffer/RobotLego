#include <iostream>
#include "case.h"
#include"deplacement.h"

Case::Case(int x, int y):
    c_visited(false),
    c_x(x),
    c_y(y)
{
}


Case::~Case(){

}

void Case::setVisited(bool v){
    this->c_visited = v;
}
bool Case::getVisited(){
    return this->c_visited;
}

Deplacement Case::getDeplacement(int dir){
//TODO faire des constantes pour le déplacement
}

void Case::createNeighbor(Deplacement *d, int dir){
    this->c_neighbor[dir] = d;
}
