#include "representation.h"
#include "robot.h"
#include "squareexploration.h"
#include "connection.h"
#include "wall_dir.h"
#include "wall_dir_scan.h"
#include "murs_impasse.h"

#include <iostream>
using namespace std;

#include <mutex>
std::mutex my_mutex;

//Autre includes éventuel (connection ou autre)

/*
 * VERSION 1 : Permet de déplacer un robot  vers la case de départ d'un autre robots.
Tout en permettant des actions dans chaque cases.
*/

/*
 * VERSION2 :Amélioration de la V1, on rajoute le fait qu'on à un labyrinthe d'une
 * taille trop grande.
 * Donc on divise le maze en deux carrés distinct.
 */

int test_astar (repr* maze,Robot* robot,int x_goal, int y_goal)
{
    if (find_path_ricochet (0, 0, x_goal, y_goal, conf::SIZE_Y - 1, conf::SIZE_X - 1,maze,robot) == -1)
    {
        cout << "PAS DE CHEMIN ! " << endl;
    }
    else
    {
        cout << "CHEMIN ! ENVOYER LES DEUX ROBOTS VERS COINS !!! " << endl;
        return 0;
    }

    if (find_path_ricochet (0, conf::SIZE_Y - 1, x_goal, y_goal, conf::SIZE_Y - 1, conf::SIZE_X - 1,maze,robot) == -1)
    {
        cout << "PAS DE CHEMIN ! " << endl;
    }
    else
    {
        cout << "CHEMIN ! ENVOYER LES DEUX ROBOTS VERS COINS !!! " << endl;
        return 0;
    }


    if (find_path_ricochet (conf::SIZE_X - 1,0,  x_goal, y_goal, conf::SIZE_Y - 1, conf::SIZE_X - 1,maze,robot) == -1)
    {
        cout << "PAS DE CHEMIN ! " << endl;
    }
    else
    {
        cout << "CHEMIN ! ENVOYER LES DEUX ROBOTS VERS COINS !!! " << endl;
        return 0;
    }

    if (find_path_ricochet (conf::SIZE_X - 1,conf::SIZE_Y - 1,  x_goal, y_goal, conf::SIZE_Y - 1, conf::SIZE_X - 1,maze,robot) == -1)
    {
        cout << "PAS DE CHEMIN ! " << endl;
    }
    else
    {
        cout << "CHEMIN ! ENVOYER LES DEUX ROBOTS VERS COINS !!! " << endl;
        return 0;
    }
    return -1;
}


void squareExploration(Robot *robot, repr* maze, int x_goal, int y_goal){

    /*===========TRAITEMENT INITIAUX============*/
    //On check la taille du labyrinthe afin de voir le chemin à prendre ( V2 )
    if(conf::SIZE_Y <= 12){
        //Cas simple
        simpleCase(robot,maze,x_goal,y_goal);
    }else{
        //Cas complexe
        complexeCase(robot,maze,x_goal,y_goal);
        cout << "ON fini le squar eplo " << endl;
    }

    //On est a la case arrivée
}

/*========================================
 *             CASE SIMPLE (12x12 max)
 * =====================================*/
void simpleCase(Robot *robot,repr* maze, int x_goal, int y_goal){
    int initPos = 0;
    int tour = 0;
    while(tour < 2){

        //On check  de quel coté est le robot initialement
        if(robot->x == 0 && robot->y == 0){
            //Le robot est en haut à gauche)
            initPos = 1;
            //send_dir(FOO);
        }else if(robot->x == 0 && robot->y == (conf::SIZE_Y-1)){
            //Le robot est en haut à droite
            initPos = 2;
            //send_dir(FOO);

        }else if(robot->x == (conf::SIZE_X-1) && robot->y == 0){
            //Le robot est en bas à gauche
            initPos = 3;
            //send_dir(FOO);

        }
        else if(robot->x == (conf::SIZE_X-1) && robot->y == (conf::SIZE_Y-1)){
            //Le robot est en bas à droite
            initPos = 4;
            //send_dir(FOO);

        }
        /*==========REALISATION DE L'EXPLORATION==========*/
        bool cond = true;

        //Premier déplacement

        while(cond){
            //On déplace
            switch(initPos){
            case 1:
                //send_deplacement(UP);
                //VERIF ICI ?
                robot->y++;
                if(robot->y == (conf::SIZE_Y-1)){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }
                break;
            case 2:
                //send_deplacement(RIGHT);
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y,maze,*robot) == -1){cond = false; break;}
                robot->x++;
                if(robot->x == (conf::SIZE_X-1)){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }
                break;
            case 3:
                //send_deplacement(LEFT);
                //VERIF?
                robot->x--;
                if(robot->x == 0){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }

                break;
            case 4:
                //send_deplacement(DOWN);
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y,maze,*robot) == -1){cond = false; break;}
                robot->y--;
                if(robot->y == 0){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }
                break;
            default :cond = false; //On est ici si il y a une erreur sur le placement du robot au début
                break;
            }
        }
        tour++;
    }
}




/*========================================
 *         CASE COMPLEXE (13x13 min)
 * =====================================*/
void complexeCase(Robot *robot, repr* maze, int x_goal, int y_goal){
    /*******************************
     *    TRAITEMENT DE LA TAILLE
     * *****************************/
    int middleR1 = (conf::SIZE_Y/2)+1;
    int middleR2 = middleR1+1;
    int initPos = 0;
    int receive;
    bool cond = true;

    /*******************************
     *    DEPART INITIAL DU ROBOT
     * *****************************/
    //On repère si on est sur un robot R1 ou un robot R2
    if(robot->x == 0 && robot->y == 0){
        //le robot est en haut à gauche
        initPos = 1;
    }else if(robot->x == 0 && robot->y == (conf::SIZE_Y-1)){
        //le robot est en haut à droite
        initPos = 2;
    }else if(robot->x == (conf::SIZE_X-1) && robot->y == 0){
        //le robot est en bas à gauche
        initPos = 3;
    }else if(robot->x == (conf::SIZE_X-1) && robot->y == (conf::SIZE_Y-1)){
        //le robot est en bas à droite
        initPos = 4;
    }


    /*******************************
     *    DEPLACEMENT DU ROBOT
     * *****************************/
    //--------------------------------------------------------------
    //Premier déplacement
    //--------------------------------------------------------------
    while(cond){
        //On déplace
        switch(initPos){
        case 1:


            //Si pas de murs en face de notre direction
            //On envoie au robot la direction
            //On recois les nouvelles informations qu'on enregistre dans reper

            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
            {
                cout << "DEPLACEMENT UP ! " << endl;
                robot->dir = UP;
                robot->dir_scan = RIGHT;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->y++;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan  (robot,receive,maze);
                my_mutex.unlock();

                drawVisited(maze, robot);

            }

            //Murs en face de nous !!!!
            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
            {
                cout <<" MUR UP " << endl;
                direction_UP_murs_UP_1 (robot,maze,robot->x, robot->y);
            }
            if(robot->y == middleR1){
                //On a finis le premier déplacement latéral
                cond = false;
                cout << "TEST RICOCHET " << endl;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, 0, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            break;
        case 2:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}

            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
            {
                 cout << "DEPLACEMENT DOWN ! " << endl;
                robot->dir = DOWN;
                robot->dir_scan = RIGHT;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->y--;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }

            //Murs en face de nous !!!!
            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
            {
                direction_DOWN_murs_DOWN_2 (robot,maze,robot->x, robot->y);
            }

            if(robot->y == middleR2){
                //On a finis le premier déplacement latéral
                cond = false;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, conf::SIZE_Y - 1, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            break;

        }
    }

    //--------------------------------------------------------------
    //Second déplacement
    //--------------------------------------------------------------
    cond =true;
    while(cond){
        switch(initPos){
        case 1:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}

            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
            {
                 cout << "DEPLACEMENT RIGHT ! x : " << robot->x << " y : " << robot->y << endl;
                robot->dir = RIGHT;
                robot->dir_scan = DOWN;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->x++;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }


            if(robot->x == (conf::SIZE_X -1)){
                //On a finis le premier déplacement latéral
                cond = false;
                cout << "FIN DEPLACEMENT RIGHT ! " << endl;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, 0, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                //Murs en face de nous !!!!
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
                {
                    cout << "MURS RIGHT " << endl;
                    direction_RIGHT_murs_RIGHT_3 (robot, maze, robot->x, robot->y);
                }
            }
            break;
        case 2:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}

            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
            {
                 cout << "DEPLACEMENT RIGHT ! " << endl;
                robot->dir = RIGHT;
                robot->dir_scan = UP;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->x++;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }

            //Murs en face de nous !!!!


            if(robot->x == (conf::SIZE_X-1)){
                //On a finis le premier déplacement latéral
                cond = false;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, conf::SIZE_Y - 1, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
                {
                   direction_RIGHT_murs_RIGHT_4 (robot, maze, robot->x, robot->y);
                }
            }
            break;
        }
    }

    //--------------------------------------------------------------
    //Troisième déplacement
    //--------------------------------------------------------------
    cond =true;
    while(cond){
        switch(initPos){
        case 1:

            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}

            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
            {
                 cout << "DEPLACEMENT DOWN ! " << endl;
                robot->dir = DOWN;
                robot->dir_scan = LEFT;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->y--;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }




            if(robot->y == 0){
                //On a finis le premier déplacement latéral
                cond = false;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, conf::SIZE_Y - 1, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                //Murs en face de nous !!!!
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
                {
                   direction_DOWN_murs_DOWN_6 (robot,maze,robot->x, robot->y);
                }
            }
            break;
        case 2:

            //send_deplacement(UP);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}

            cout << "troisième deplacement  UP ! " << endl;
            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
            {
                 cout << "DEPLACEMENT UP ! " << endl;
                robot->dir = UP;
                robot->dir_scan = LEFT;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->y++;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }




            if(robot->y == (conf::SIZE_Y -1)){
                //On a finis le premier déplacement latéral
                cond = false;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, 0, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                //Murs en face de nous !!!!
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
                {
                   direction_UP_murs_UP_5 (robot,maze,robot->x , robot->y );
                }
            }
            break;
        }
    }
    //--------------------------------------------------------------
    //Dernier déplacement
    //--------------------------------------------------------------
    cond =true;
    while(cond){
        switch(initPos){
        case 1:
            //send_deplacement(LEFT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
            {
                 cout << "DEPLACEMENT LEFT ! " << endl;
                robot->dir = LEFT;
                robot->dir_scan = UP;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->x--;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }




            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;
                cout << "ON A FINI LE LAB ! " << endl;
                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, conf::SIZE_Y - 1, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                //Murs en face de nous !!!!
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
                {
                   direction_LEFT_murs_LEFT_8 (robot,maze,robot->x, robot->y);
                }
            }
            break;
        case 2:

            //send_deplacement(LEFT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
            if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
            {
                 cout << "DEPLACEMENT LEFT ! " << endl;
                robot->dir = LEFT;
                robot->dir_scan = DOWN;
                send_direction (robot->id, robot->dir,robot->dir_scan);
                robot->x--;

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir (robot,receive,maze);
                my_mutex.unlock();

                send_direction (robot->id,0,0);

                receive = recevoir(robot->id);
                while(!my_mutex.try_lock()) {};
                ad_information_dir_scan(robot,receive,maze);
                my_mutex.unlock();
            }



            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;

                //A FAIT LE A* RICOCHET POUR SAVOIR SI CA MARCHE OU PAS !!!
//                cout << "TEST RICOCHET " << endl;
//                if(test_astar (maze,robot, x_goal,  y_goal) == 0)
//                {
//                    find_path_not_ricochet (robot->x,robot->y, 0, 0, maze, robot);
//                    envoi_chemin_ricochet (robot);
//                }
            }
            else
            {
                //Murs en face de nous !!!!
                if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
                {
                   direction_LEFT_murs_LEFT_7 (robot,maze,robot->x, robot->y);
                }
            }
            break;

        }
    }
}


