#include "representation.h"
#include "global.h"

std::vector<int> setupWall(int w, int h){
    std::vector<int> wall(w*h);
    for(  int i = 0 ; i < w ; i++ ){
        for(  int y = 0 ; y < h ; y++ ){
            //On met en place les mur pour la ligne en haut UP
            if(i==0){
                wall[y] += UP;
            }
            //On met en place les murs pour la ligne du bas DOWN
            if(i==(w-1)){
                wall[getIndexWallVisited(w-1,y)]+= DOWN;
            }
            //On met en place les murs pour la gauche LEFT
            if(y==0){
                wall[getIndexWallVisited(i,0)] += LEFT;
            }
            //On met en place les murs pour la droite RIGHT
            if(y==h-1){
                wall[getIndexWallVisited(i,h-1)] += RIGHT;
            }
        }
    }
    return wall;
}

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

