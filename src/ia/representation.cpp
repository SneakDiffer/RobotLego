#include "representation.h"
#include "global.h"


int getIndexWallVisited(int row, int col){
    //On vérifie qu'on est bien dans le tableau
    if(row < conf::SIZE_X && col < conf::SIZE_Y){
        return (conf::SIZE_Y*row)+col;
    }else{
        return -1;
    }
}

int getIndexAdj(int row, int col){
    //On vérifie qu'on est bien dans le tableau
    if(row < conf::SIZE_X*conf::SIZE_Y && col < conf::SIZE_X*conf::SIZE_Y){
        return ((conf::SIZE_Y*conf::SIZE_X)*row)+col;
    }else{
        return -1;
    }
}

