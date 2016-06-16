#include "representation.h"
#include "robot.h"
#include "squareexploration.h"
#include <iostream>
using namespace std;
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

void squareExploration(Robot *robot, repr maze){

    /*===========TRAITEMENT INITIAUX============*/
    //On check la taille du labyrinthe afin de voir le chemin à prendre ( V2 )
    if(conf::SIZE_Y <= 12){
        //Cas simple
        simpleCase(robot,maze);
    }else{
        //Cas complexe
        complexeCase(robot,maze);
    }

    //On est a la case arrivée
}

/*========================================
 *             CASE SIMPLE (12x12 max)
 * =====================================*/
void simpleCase(Robot *robot,repr maze){
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
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}
                robot->y++;
                if(robot->y == (conf::SIZE_Y-1)){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }
                break;
            case 2:
                //send_deplacement(RIGHT);
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}
                robot->x++;
                if(robot->x == (conf::SIZE_X-1)){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }
                break;
            case 3:
                //send_deplacement(LEFT);
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
                robot->x--;
                if(robot->x == 0){
                    //On a finis le premier déplacement latéral
                    cond = false;
                }

                break;
            case 4:
                //send_deplacement(DOWN);
                //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}
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
 *         CASE SIMPLE (13x13 min)
 * =====================================*/
void complexeCase(Robot *robot, repr maze){
    /*******************************
     *    TRAITEMENT DE LA TAILLE
     * *****************************/
    int middleR1 = (conf::SIZE_Y/2)+1;
    int middleR2 = middleR1+1;
    int initPos = 0;
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
            //send_deplacement(UP);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}
            robot->y++;
            if(robot->y == middleR1){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 2:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}
            robot->y--;
            if(robot->y == middleR2){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 3:
            //send_deplacement(LEFT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x--;
            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;
            }

            break;
        case 4:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x--;
            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        default :cond = false; //On est ici si il y a une erreur sur le placement du robot au début
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
            robot->x++;
            if(robot->x == (conf::SIZE_X -1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 2:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x++;
            if(robot->x == (conf::SIZE_X-1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 3:
            //send_deplacement(UP);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}
            robot->y++;
            if(robot->y == middleR1){
                //On a finis le premier déplacement latéral
                cond = false;
            }

            break;
        case 4:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}
            robot->y--;
            if(robot->y == middleR2){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        default :cond = false; //On est ici si il y a une erreur sur le placement du robot au début
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
            //send_deplacement(UP);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}
            robot->y++;
            if(robot->y == (conf::SIZE_Y -1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 2:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}
            robot->y--;
            if(robot->y == 0){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 3:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x++;
            if(robot->x == (conf::SIZE_X-1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }

            break;
        case 4:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x+1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x++;
            if(robot->x == (conf::SIZE_X-1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        default :cond = false; //On est ici si il y a une erreur sur le placement du robot au début
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
            robot->x--;
            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 2:
            //send_deplacement(RIGHT);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x-1,robot->y,maze,*robot) == -1){cond = false; break;}
            robot->x--;
            if(robot->x == 0){
                //On a finis le premier déplacement latéral
                cond = false;
            }
            break;
        case 3:
            //send_deplacement(UP);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y+1,maze,*robot) == -1){cond = false; break;}
            robot->y++;
            if(robot->y == (conf::SIZE_Y-1)){
                //On a finis le premier déplacement latéral
                cond = false;
            }

            break;
        case 4:
            //send_deplacement(DOWN);
            //if(find_path_not_ricochet(robot->x,robot->y,robot->x,robot->y-1,maze,*robot) == -1){cond = false; break;}
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
}


