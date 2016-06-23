
#include "src/ia/wall_dir_scan.h"


void completement_ad_information_dir_scan  (Robot* robot,repr *reper, int nb_case,bool inverse)
{
    if(inverse)
    {
        switch(robot->dir_scan)
        {
            case UP:
                if(robot->y + nb_case < conf::SIZE_Y)
                {
                    reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] = reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] | DOWN;
                    reper->visited[getIndexWallVisited(robot->x,robot->y + nb_case)]  = reper->visited[getIndexWallVisited(robot->x,robot->y + nb_case)] | DOWN;
                }
                break;
            case DOWN:
                if(robot->y - nb_case >= 0 )
                {
                    reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] =  reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] | UP;
                    reper->visited[getIndexWallVisited(robot->x,robot->y - nb_case)] =  reper->visited[getIndexWallVisited(robot->x,robot->y - nb_case)] | UP;
                }
                break;
            case LEFT:
                if(robot->x - nb_case >= 0)
                {
                    reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] |  RIGHT;
                    reper->visited[getIndexWallVisited(robot->x - nb_case,robot->y )] = reper->visited[getIndexWallVisited(robot->x - nb_case,robot->y )] | RIGHT;
                }
                break;
            case RIGHT:
                if(robot->x + nb_case < conf::SIZE_X)
                {
                    reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] | LEFT;
                    reper->visited[getIndexWallVisited(robot->x + nb_case,robot->y )] = reper->visited[getIndexWallVisited(robot->x + nb_case,robot->y )] | LEFT;
                }
                break;
        }
    }
    else
    {
        switch(robot->dir_scan)
        {
            case UP:
                if(robot->y + nb_case < conf::SIZE_Y)
                {
                    reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] =  reper->wall[getIndexWallVisited(robot->x,robot->y + nb_case)] | robot->dir_scan;
                    reper->visited[getIndexWallVisited(robot->x,robot->y + nb_case)] = reper->visited[getIndexWallVisited(robot->x,robot->y + nb_case)] | robot->dir_scan;
                }
                break;
            case DOWN:
               if(robot->y - nb_case >= 0)
               {
                reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] = reper->wall[getIndexWallVisited(robot->x,robot->y - nb_case)] | robot->dir_scan;
                reper->visited[getIndexWallVisited(robot->x,robot->y - nb_case)] = reper->visited[getIndexWallVisited(robot->x,robot->y - nb_case)] | robot->dir_scan;
               }
                break;
            case LEFT:
                    if(robot->x - nb_case >= 0)
                    {
                        reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x - nb_case,robot->y )] | robot->dir_scan;
                        reper->visited[getIndexWallVisited(robot->x - nb_case,robot->y )] = reper->visited[getIndexWallVisited(robot->x - nb_case,robot->y )] | robot->dir_scan;
                    }
                   break;
            case RIGHT:
                    if(robot->x + nb_case < conf::SIZE_X)
                    {
                        reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] = reper->wall[getIndexWallVisited(robot->x + nb_case,robot->y )] | robot->dir_scan;
                        reper->visited[getIndexWallVisited(robot->x + nb_case,robot->y )] = reper->visited[getIndexWallVisited(robot->x + nb_case,robot->y )] |  robot->dir_scan;
                    }
                break;
        }
    }
}

void wall_visited_dir_scan  (Robot* robot,repr *reper,int nb_case)
{
    int i=0;
        switch(robot->dir_scan)
        {
            case UP:
                for(i = 0; (i < nb_case) && ((robot->y + i) < conf::SIZE_Y ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x,robot->y + i)] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | UP;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot->y + i) < conf::SIZE_Y); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x,robot->y + i)] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | DOWN;
                }
                break;
            case DOWN:
                for(i = 0; (i < nb_case) && ((robot->y - i)  >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x ,robot->y - i)] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | DOWN;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot->y - i) >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x + i,robot->y - i)] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | UP;
                }
                break;
            case LEFT:
                for(i = 0;(i < nb_case) && ((robot->x - i)  >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x - i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | LEFT;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot->x - i) >= 0); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x - i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | RIGHT;
                }
                break;
            case RIGHT:

                for(i = 0; (i < nb_case) && ((robot->x + i)  < conf::SIZE_X ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x + i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | RIGHT;
                }
                i = 1;
                for(i = 1; (i < nb_case + 1) && ((robot->x + i) < conf::SIZE_X ); i ++)
                {
                    reper->visited[getIndexWallVisited(robot->x + i,robot->y )] = reper->visited[getIndexWallVisited(robot->x + i,robot->y )] | LEFT;
                }
                break;
        }

}

void ad_information_dir_scan (Robot* robot, int distance, repr* reper)
{

    if(distance <= 35)
    {
         reper->wall[getIndexWallVisited(robot->x,robot->y)] = reper->wall[getIndexWallVisited(robot->x,robot->y)] | robot->dir_scan;
         reper->visited[getIndexWallVisited(robot->x,robot->y)] = reper->visited[getIndexWallVisited(robot->x,robot->y)] |  robot->dir_scan;
         completement_ad_information_dir_scan  ( robot,reper,1,true);

    }
    if(distance > 35 && distance <= 75)
    {
        wall_visited_dir_scan (robot,reper,1);
        completement_ad_information_dir_scan  ( robot,reper,1,false);
        completement_ad_information_dir_scan  ( robot,reper,2,true);

    }
    if(distance > 75 && distance <= 115)
    {
        wall_visited_dir_scan (robot,reper,2);
        completement_ad_information_dir_scan  ( robot,reper,2,false);
        completement_ad_information_dir_scan  ( robot,reper,3,true);

    }
    if(distance > 115 && distance <= 155)
    {
        wall_visited_dir_scan (robot,reper,3);
        completement_ad_information_dir_scan  ( robot,reper,3,false);
        completement_ad_information_dir_scan  ( robot,reper,4,true);

    }
    if(distance > 155 && distance <= 195)
    {
        wall_visited_dir_scan (robot,reper,4);
        completement_ad_information_dir_scan  ( robot,reper,4,false);
        completement_ad_information_dir_scan  ( robot,reper,5,true);

    }
    if(distance > 195 && distance <= 235)
    {

        wall_visited_dir_scan (robot,reper,5);
        completement_ad_information_dir_scan  ( robot,reper,5,false);
        completement_ad_information_dir_scan  ( robot,reper,6,true);

    }
    if(distance > 235)
    {
        wall_visited_dir_scan (robot,reper,6);

    }
}


void affiche_visited (repr* reper,int x, int y, int dir)
{
    if((reper->visited[getIndexWallVisited(x,y)] & dir) != 0)
    {
        cout << "Visited " << dir << " " << x << y << endl;
    }
    else
    {
        cout << "Pas visited " << dir << " " << x << y << endl;
    }
}
