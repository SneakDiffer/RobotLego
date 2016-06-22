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

void completement_ad_information (Robot robot,repr *reper, int nb_case,bool inverse)
{
    if(inverse)
    {
        switch(robot.dir_scan)
        {
            case UP:
                if(robot.y + nb_case < conf::SIZE_Y)
                {
                    reper->wall[getIndexWallVisited(robot.x,robot.y + nb_case)] = reper->wall[getIndexWallVisited(robot.x,robot.y + nb_case)] | DOWN;
                    reper->visited[getIndexWallVisited(robot.x,robot.y + nb_case)]  = reper->visited[getIndexWallVisited(robot.x,robot.y + nb_case)] | DOWN;
                }
                break;
            case DOWN:
                if(robot.y - nb_case >= 0 )
                {
                    reper->wall[getIndexWallVisited(robot.x,robot.y - nb_case)] =  reper->wall[getIndexWallVisited(robot.x,robot.y - nb_case)] | UP;
                    reper->visited[getIndexWallVisited(robot.x,robot.y - nb_case)] =  reper->visited[getIndexWallVisited(robot.x,robot.y - nb_case)] | UP;
                }
                break;
            case LEFT:
                if(robot.x - nb_case >= 0)
                {
                    reper->wall[getIndexWallVisited(robot.x - nb_case,robot.y )] = reper->wall[getIndexWallVisited(robot.x - nb_case,robot.y )] |  RIGHT;
                    reper->visited[getIndexWallVisited(robot.x - nb_case,robot.y )] = reper->visited[getIndexWallVisited(robot.x - nb_case,robot.y )] | RIGHT;
                }
                break;
            case RIGHT:
                if(robot.x + nb_case < conf::SIZE_X)
                {
                    reper->wall[getIndexWallVisited(robot.x + nb_case,robot.y )] = reper->wall[getIndexWallVisited(robot.x + nb_case,robot.y )] | LEFT;
                    reper->visited[getIndexWallVisited(robot.x + nb_case,robot.y )] = reper->visited[getIndexWallVisited(robot.x + nb_case,robot.y )] | LEFT;
                }
                break;
        }
    }
    else
    {
        switch(robot.dir_scan)
        {
            case UP:
                if(robot.y + nb_case < conf::SIZE_Y)
                {
                    reper->wall[getIndexWallVisited(robot.x,robot.y + nb_case)] =  reper->wall[getIndexWallVisited(robot.x,robot.y + nb_case)] | robot.dir_scan;
                    reper->visited[getIndexWallVisited(robot.x,robot.y + nb_case)] = reper->visited[getIndexWallVisited(robot.x,robot.y + nb_case)] | robot.dir_scan;
                }
                break;
            case DOWN:
               if(robot.y - nb_case >= 0)
               {
                reper->wall[getIndexWallVisited(robot.x,robot.y - nb_case)] = reper->wall[getIndexWallVisited(robot.x,robot.y - nb_case)] | robot.dir_scan;
                reper->visited[getIndexWallVisited(robot.x,robot.y - nb_case)] = reper->visited[getIndexWallVisited(robot.x,robot.y - nb_case)] | robot.dir_scan;
               }
                break;
            case LEFT:
                    if(robot.x - nb_case >= 0)
                    {
                        reper->wall[getIndexWallVisited(robot.x - nb_case,robot.y )] = reper->wall[getIndexWallVisited(robot.x - nb_case,robot.y )] | robot.dir_scan;
                        reper->visited[getIndexWallVisited(robot.x - nb_case,robot.y )] = reper->visited[getIndexWallVisited(robot.x - nb_case,robot.y )] | robot.dir_scan;
                    }
                   break;
            case RIGHT:
                    if(robot.x + nb_case < conf::SIZE_X)
                    {
                        reper->wall[getIndexWallVisited(robot.x + nb_case,robot.y )] = reper->wall[getIndexWallVisited(robot.x + nb_case,robot.y )] | robot.dir_scan;
                        reper->visited[getIndexWallVisited(robot.x + nb_case,robot.y )] = reper->visited[getIndexWallVisited(robot.x + nb_case,robot.y )] |  robot.dir_scan;
                    }
                break;
        }
    }
}

void wall_visited (Robot robot,repr *reper,int nb_case)
{
    int i=0;
        switch(robot.dir_scan)
        {
            case UP:
                for(i = 0; (i < nb_case) && ((robot.y + nb_case) - 1 < conf::SIZE_Y ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x,robot.y + i)] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | UP;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot.y + nb_case) < conf::SIZE_Y); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x,robot.y + i)] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | DOWN;
                }
                break;
            case DOWN:
                for(i = 0; (i < nb_case) && ((robot.y - nb_case) - 1 >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x ,robot.y - i)] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | DOWN;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot.y - nb_case) >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x + i,robot.y - i)] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | UP;
                }
                break;
            case LEFT:
                for(i = 0;(i < nb_case) && ((robot.x - nb_case) - 1 >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x - i,robot.y )] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | LEFT;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot.x - nb_case) >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x - i,robot.y )] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | RIGHT;
                }
                break;
            case RIGHT:

                for(i = 0; (i < nb_case) && ((robot.x + nb_case) - 1 < conf::SIZE_X ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x + i,robot.y )] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | RIGHT;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot.x + nb_case) < conf::SIZE_X ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot.x + i,robot.y )] = reper->visited[getIndexWallVisited(robot.x + i,robot.y )] | LEFT;
                }
                break;
        }

}

void ad_information (Robot robot, int distance, repr* reper)
{

    if(distance <= 35)
    {
         reper->wall[getIndexWallVisited(robot.x,robot.y)] = reper->wall[getIndexWallVisited(robot.x,robot.y)] | robot.dir_scan;
         reper->visited[getIndexWallVisited(robot.x,robot.y)] = reper->wall[getIndexWallVisited(robot.x,robot.y)] |  robot.dir_scan;
         completement_ad_information ( robot,reper,1,true);
    }
    if(distance > 35 && distance <= 75)
    {
        wall_visited(robot,reper,1);
        completement_ad_information ( robot,reper,1,false);
        completement_ad_information ( robot,reper,2,true);
    }
    if(distance > 75 && distance <= 115)
    {
        wall_visited(robot,reper,2);
        completement_ad_information ( robot,reper,2,false);
        completement_ad_information ( robot,reper,3,true);
    }
    if(distance > 115 && distance <= 155)
    {
        wall_visited(robot,reper,3);
        //completement_ad_information ( robot,reper,3,false);
        //completement_ad_information ( robot,reper,4,true);
    }
    if(distance > 155 && distance <= 195)
    {
        wall_visited(robot,reper,4);
        completement_ad_information ( robot,reper,4,false);
        completement_ad_information ( robot,reper,5,true);
    }
    if(distance > 195 && distance <= 235)
    {

        wall_visited(robot,reper,5);
        completement_ad_information ( robot,reper,5,false);
        completement_ad_information ( robot,reper,6,true);
    }
    if(distance > 235)
    {
        wall_visited(robot,reper,6);
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
