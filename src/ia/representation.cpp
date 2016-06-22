#include "representation.h"
#include "global.h"



std::vector<int> setupWall(int w, int h){
    std::vector<int> wall(w*h);
    for(  int i = 0 ; i < w ; i++ ){
        for(  int y = 0 ; y < h ; y++ ){
            //On met en place les mur pour la ligne en haut LEFT
            if(i==0){
                wall[y] += LEFT;
            }
            //On met en place les murs pour la ligne du bas RIGHT
            if(i==(w-1)){
                wall[getIndexWallVisited(w-1,y)]+= RIGHT;
            }
            //On met en place les murs pour la gauche DOWN
            if(y==0){
                wall[getIndexWallVisited(i,0)] += DOWN;
            }
            //On met en place les murs pour la droite UP
            if(y==h-1){
                wall[getIndexWallVisited(i,h-1)] += UP;
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


void draw(repr maze, Robot robot){
    //Premièrement on clear
    system("clear");
    //On trace
    for(int i = 0 ; i < conf::SIZE_X ; i++){
        for(int y = 0 ; y < conf::SIZE_Y ; y++){
            if((maze.wall[getIndexWallVisited(i,y)] & LEFT) != LEFT){
                std::cout << KBLU <<" ---" << KNRM;
            }else{
                std::cout << KRED <<" ---" << KNRM;
            }

        }
        std::cout << "" << endl;
        for(int z = 0 ; z < conf::SIZE_Y ; z++){
            if(robot.x == i && robot.y == z){
                if((maze.wall[getIndexWallVisited(i,z)] & DOWN) != DOWN ){
                                std::cout << KBLU <<"|" << KNRM << " o ";
                            }else{
                                std::cout << KRED <<"|" << KNRM << " o ";
                            }
            }
            else if((maze.wall[getIndexWallVisited(i,z)] & DOWN) != DOWN ){
                std::cout << KBLU <<"|   " << KNRM;
            }else{
                std::cout << KRED <<"|   " << KNRM;
            }
        }
        if((maze.wall[getIndexWallVisited(i,conf::SIZE_Y-1)] & UP) != UP){
            std::cout << KBLU <<"|" << KNRM;
        }else{
            std::cout << KRED <<"|" << KNRM;
        }
        std::cout << "" << endl;
    }
    for(int w = 0 ; w < conf::SIZE_Y ; w++){
        if((maze.wall[getIndexWallVisited(conf::SIZE_X-1,w)] & RIGHT) != RIGHT){
            std::cout << KBLU <<" ---" << KNRM;
        }else{
            std::cout << KRED <<" ---" << KNRM;
        }
    }
    std::cout << "" << endl;

}

void drawVisited(repr maze, Robot robot){
    //Premièrement on clear
    system("clear");
    //On trace
    for(int i = 0 ; i < conf::SIZE_X ; i++){
        for(int y = 0 ; y < conf::SIZE_Y ; y++){
            if((maze.visited[getIndexWallVisited(i,y)] & LEFT) != LEFT){
                std::cout << KYEL <<" ---" << KNRM;
            }else{
                std::cout << KBLU <<" ---" << KNRM;
            }

        }
        std::cout << "" << endl;
        for(int z = 0 ; z < conf::SIZE_Y ; z++){
            if(robot.x == i && robot.y == z){
                if((maze.visited[getIndexWallVisited(i,z)] & DOWN) != DOWN ){
                                std::cout << KYEL <<"|" << KNRM << " o ";
                            }else{
                                std::cout << KBLU <<"|" << KNRM << " o ";
                            }
            }
            else if((maze.visited[getIndexWallVisited(i,z)] & DOWN) != DOWN ){
                std::cout << KYEL <<"|   " << KNRM;
            }else{
                std::cout << KBLU <<"|   " << KNRM;
            }
        }
        if((maze.visited[getIndexWallVisited(i,conf::SIZE_Y-1)] & UP) != UP){
            std::cout << KYEL <<"|" << KNRM;
        }else{
            std::cout << KBLU <<"|" << KNRM;
        }
        std::cout << "" << endl;
    }
    for(int w = 0 ; w < conf::SIZE_Y ; w++){
        if((maze.visited[getIndexWallVisited(conf::SIZE_X-1,w)] & RIGHT) != RIGHT){
            std::cout << KYEL <<" ---" << KNRM;
        }else{
            std::cout << KBLU <<" ---" << KNRM;
        }
    }
    std::cout << "" << endl;

}
