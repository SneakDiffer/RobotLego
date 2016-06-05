#include <iostream>
#include "deplacement.h"
#include "case.h"
#include "coord.h"

    Deplacement::Deplacement(int dir){
        this->d_dir = dir;
    }
    Deplacement::~Deplacement(){
    }
    void Deplacement::setPossible(bool b){
        this->d_possible = b;
    }

    bool Deplacement::isPossible(){
        return this->d_possible;
    }

    int Deplacement::getDir(){
        return this->d_dir;
    }

    void Deplacement::setG(int g){
        this->d_G = g;
    }

    void Deplacement::setH(int h){
        this->d_H;
    }

    int Deplacement::getF(){
        return this->d_F;
    }

    int Deplacement::getG(){
        return this->d_G;
    }
    int Deplacement::getH(){
        return this->d_H;
    }


