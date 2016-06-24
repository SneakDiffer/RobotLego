#include "src/ia/wall_dir.h"


void completement_ad_information_dir (Robot* robot,repr *reper, int nb_case)
{
    switch(robot->dir)
           {
               case UP:
                    if((robot->y + nb_case) < conf::SIZE_Y)
                    {
                    reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] = reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] | UP;
                    }
                    if((robot->y + nb_case + 1 )< conf::SIZE_Y)
                    {
                    reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case + 1)] = reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case + 1)] | DOWN;
                    }
                    break;
               case DOWN:
                    if(robot->y - nb_case >= 0)
                    {
                    reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] = reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] | DOWN;
                    }
                    if(robot->y - nb_case - 1 >= 0)
                    {
                    reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case - 1)] = reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case - 1)] | UP;
                    }
                    break;
               case LEFT:
                    if(robot->x - nb_case >= 0)
                    {
                    reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] | LEFT;
                    }
                    if(robot->x - nb_case - 1 >= 0)
                    {

                    reper->wall[getIndexWallVisited(robot->x - nb_case - 1,robot->y )] = reper->wall[getIndexWallVisited(robot->x - nb_case - 1,robot->y )] | RIGHT;
                    }
                    break;
               case RIGHT:
                    if(robot->x + nb_case < conf::SIZE_X)
                    {
                    reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] | RIGHT;
                    }
                    if(robot->x + nb_case + 1  < conf::SIZE_X)
                    {
                    reper->wall[getIndexWallVisited(robot->x + nb_case + 1,robot->y )] = reper->wall[getIndexWallVisited(robot->x + nb_case + 1,robot->y )] | LEFT;
                    }
                    break;
           }
}

void wall_visited_dir (Robot* robot,repr *reper,int nb_case)
{
    int i;
    switch(robot->dir)
           {
               case UP:
                   for(i = 0; (i < nb_case) && ((robot->y + i)  < conf::SIZE_Y ); i ++)
                   {
                       reper->visited[getIndexWallVisited(robot->x,robot->y + i)] = reper->visited[getIndexWallVisited(robot->x,robot->y + i)] | UP;
                   }
                   i = 1;
                   for(i = 1; (i < nb_case + 1) && ((robot->y + i) < conf::SIZE_Y); i ++)
                   {
                       reper->visited[getIndexWallVisited(robot->x,robot->y + i)] = reper->visited[getIndexWallVisited(robot->x,robot->y + i)] | DOWN;
                   }
                   break;
               case DOWN:
                    for(i = 0; (i < nb_case) && ((robot->y - i)  >= 0 ); i ++)
                    {
                        reper->visited[getIndexWallVisited(robot->x,robot->y - i)] = reper->visited[getIndexWallVisited(robot->x,robot->y - i)] | DOWN;
                    }
                    i = 1;
                    for(i = 1; (i < nb_case + 1) && ((robot->y - i) >= 0); i ++)
                    {
                        reper->visited[getIndexWallVisited(robot->x,robot->y - i)] = reper->visited[getIndexWallVisited(robot->x,robot->y - i)] | UP;
                    }
                   break;
               case LEFT:
                    for(i = 0; (i < nb_case) && ((robot->x - i)  >= 0 ); i ++)
                    {

                        reper->visited[getIndexWallVisited(robot->x - i,robot->y )] = reper->visited[getIndexWallVisited(robot->x - i,robot->y )] | LEFT;
                    }
                    for(i = 1; (i < nb_case + 1) && ((robot->x - i) >= 0); i ++)
                    {

                        reper->visited[getIndexWallVisited(robot->x - i,robot->y )] = reper->visited[getIndexWallVisited(robot->x - i,robot->y)] | RIGHT;
                    }
                   break;
               case RIGHT:
                    for(i = 0; (i < nb_case) && ((robot->x + i)  < conf::SIZE_X ); i ++)
                    {
                        reper->visited[getIndexWallVisited(robot->x + i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | RIGHT;
                    }
                    i = 1;
                    for(i = 1; (i < nb_case + 1) && ((robot->x + i) < conf::SIZE_X); i ++)
                    {
                        reper->visited[getIndexWallVisited(robot->x + i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y)] | LEFT;
                    }
                   break;
           }

}

void ad_information_dir (Robot* robot, int distance, repr* reper)
{
    if(distance <= 35)
    {
        wall_visited_dir (robot,reper,1);
        completement_ad_information_dir (robot, reper, 0);
    }
    if(distance > 35   && distance <= 75)
    {
        wall_visited_dir (robot,reper,2);
        completement_ad_information_dir (robot, reper, 1);
    }
    if(distance > 75   && distance <= 115)
    {
        wall_visited_dir (robot,reper,3);
        completement_ad_information_dir (robot, reper, 2);
    }
    if(distance > 115   && distance <= 155)
    {
        wall_visited_dir (robot,reper,4);
        completement_ad_information_dir (robot, reper, 3);
    }
    if(distance > 155   && distance <= 195)
    {
        wall_visited_dir (robot,reper,5);
        completement_ad_information_dir (robot, reper, 4);
    }
    if(distance > 195   && distance <= 235)
    {
        wall_visited_dir (robot,reper,6);
        completement_ad_information_dir (robot, reper, 5);
    }
    if(distance > 235)
    {
        wall_visited_dir (robot,reper,7);
    }


}

