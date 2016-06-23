#include "ui/qapp.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include "src/ia/connection.h"
#include "src/ia/representation.h"
#include "src/ia/wall_dir_scan.h"
#include "src/ia/wall_dir.h"
#include "src/ia/squareexploration.h"

#include "src/ia/astar.h"
#include <thread>

#include <mutex>
std::mutex my_mutex_main;

using namespace std;


//ROBOT1 POSITION 0 0 !!!!
//COIN HAUT GAUCHE
void Robot1 (Robot robot,repr *rep)
{

    char nxt[18] = "00:16:53:18:EB:71";


        if (init_bluetooth(nxt,robot.id) < 0)      {
             cout << "Bluetooth not connected " << endl;
        }
        cout << "Bluetooth connected ! 1" << endl;

        int receive;

        //Envoie au robot la direction de la tête
        send_direction (robot.id,0,robot.dir_scan);
        //On attend le scanne direction robot
        receive = recevoir(robot.id);
        ad_information_dir (&robot,receive,rep);
        //Confirme la reception
        send_direction (robot.id,0,0);
        //On attend le scanne perpendiculaire au robot
        receive = recevoir(robot.id);
        ad_information_dir_scan  (&robot,receive,rep);


        //ALGO DE THOMAS, QUI DETERMINE LA NOUVELLE DIRECTION ROBOT + DIRECTION TËTE !!!
        squareExploration(&robot, rep,4,5);

        cout << "ON A FINI LE LAB ! " << endl;
}


//ROBOT2 POSITION 0 longeur !!!!
//COIN HAUT DROITE
void Robot2 (Robot robot,repr *rep)
{

    char my_nxt[18] = "00:16:53:1C:24:E7";

        if (init_bluetooth(my_nxt,robot.id) < 0)      {
             cout << "Bluetooth not connected" << endl;
        }
        cout << "Bluetooth connected ! " << endl;

        int receive;

        //Envoie au robot la direction de la tête
        send_direction (robot.id,0,robot.dir_scan);
        //On attend le scanne direction robot
        receive = recevoir(robot.id);
        ad_information_dir (&robot,receive,rep);
        //Confirme la reception
        send_direction (robot.id,0,0);
        //On attend le scanne perpendiculaire au robot
        receive = recevoir(robot.id);
        ad_information_dir_scan  (&robot,receive,rep);


        //ALGO DE THOMAS, QUI DETERMINE LA NOUVELLE DIRECTION ROBOT + DIRECTION TËTE !!!
        squareExploration(&robot, rep,4,5);

}


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    QApp w;
//    w.show();

//    return a.exec();


    conf::SIZE_X = 7;
    conf::SIZE_Y = 19;
    Robot robot1(1,0,0,UP,RIGHT);
   // Robot robot2(2,2,2,DOWN,RIGHT);
    repr rep(conf::SIZE_X,conf::SIZE_Y);

//    rep.visited[getIndexWallVisited(0, 2)] = RIGHT + UP + DOWN;

//    rep.visited[getIndexWallVisited(0, 3)] = RIGHT + UP + DOWN;


//    rep.wall[getIndexWallVisited(0, 3)] = RIGHT;

//    rep.wall[getIndexWallVisited(1, 3)] = RIGHT + DOWN + LEFT;


//    rep.visited[getIndexWallVisited(1, 3)] = RIGHT + UP + DOWN + LEFT;

//    rep.wall[getIndexWallVisited(1, 4)] = RIGHT + UP;
//    rep.visited[getIndexWallVisited(1, 4)] = RIGHT + UP + DOWN + LEFT;



//    rep.wall[getIndexWallVisited(0, 4)] = UP;

//    rep.visited[getIndexWallVisited(0, 4)] = RIGHT + UP + DOWN;

//    ad_information_dir (&robot1, 115, &rep);
//robot1.y = 2;


//ad_information_dir (&robot1, 75, &rep);
//affiche_visited(&rep,1, 2, UP);
//affiche_visited (&rep,1, 2, DOWN);
//affiche_visited (&rep,1, 2, LEFT);
//affiche_visited (&rep,1, 2, RIGHT);
//affiche_visited(&rep,1, 3, UP);
//affiche_visited (&rep,1,3, DOWN);
//affiche_visited (&rep,1,3, LEFT);
//affiche_visited (&rep,1,3, RIGHT);



//ad_information_dir_scan (&robot1, 75, &rep);
//affiche_visited(&rep,1, 2, UP);
//affiche_visited (&rep,1, 2, DOWN);
//affiche_visited (&rep,1, 2, LEFT);
//affiche_visited (&rep,1, 2, RIGHT);

//    find_path_not_ricochet (1, 3, 0, 2, &rep, &robot1);


   std::thread t1(Robot1,robot1,&rep);
   // std::thread t2(Robot2,robot2,&rep);

   t1.join();
    // t2.join();
draw(&rep, &robot1);
drawVisited(&rep, &robot1);
     return 0;
}
