#include "ui/qapp.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include "src/ia/connection.h"
#include "src/ia/representation.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApp w;
    w.show();

    return a.exec();

//    conf::SIZE_X = 3;
//    conf::SIZE_Y = 4;
//    Robot robot1;
//    robot1.id = 1;
//    robot1.x = 0;
//    robot1.y = 0;
//     robot1.dir_scan = RIGHT;
//     repr rep(conf::SIZE_X,conf::SIZE_Y);

//    char btaddress[18] = "00:16:53:16:13:88";
//        cout << "Hello world!" << endl;
//            // initiate bluetooth connection
//        if (init_bluetooth(btaddress,robot1.id) < 0)      {
//             cout << "marche pas " << endl;
//        }

//     reper.wall[getIndexWallVisited(robot.x,robot.y)]+= robot.dir_scan;
//      reper.visited[getIndexWallVisited(robot.x,robot.y)]+= robot.dir_scan;

     //ad_information (robot1,155,&rep);

}
