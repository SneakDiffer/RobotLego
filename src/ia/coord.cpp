#include <iostream>
#include "coord.h"

Coord::Coord(int x,int y){
    this->c_x = x;
    this->c_y = y;
}

Coord::~Coord(){
}

int Coord::getx(){
    return this->c_x;
}

int Coord::gety(){
    return this->c_y;
}

void Coord::setx(int x){
    this->c_x = x;
}

void Coord::sety(int y){
    this->c_y = y;
}
