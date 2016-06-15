#include "ui/qapp.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include "src/ia/connection.h"
#include "src/ia/representation.h"
#include <thread>
#include <mutex>
using namespace std;
std::mutex my_mutex;



void Robot1 (Robot robot,repr *rep)
{
    char nxt[18] = "00:16:53:16:13:88";


        if (init_bluetooth(nxt,robot.id) < 0)      {
             cout << "Bluetooth not connected " << endl;
        }
        cout << "Bluetooth connected ! " << endl;

        int receive;
        while(1)
        {
            receive = recevoir(robot.id);

            //On attend que la structure ne sois plus utilisée par l'autre thread
            while(!my_mutex.try_lock()){};
            ad_information (robot,receive,rep);
             my_mutex.unlock();

            //THOMAS A TOI
        }


}

void Robot2 (Robot robot,repr *rep)
{
    char my_nxt[18] = "00:16:53:1C:24:E7";

        if (init_bluetooth(my_nxt,robot.id) < 0)      {
             cout << "Bluetooth not connected" << endl;
        }
        cout << "Bluetooth connected ! " << endl;

        int receive;
        while(1)
        {
            receive = recevoir(robot.id);

            //On attend que la structure ne sois plus utilisée par l'autre thread
            while(!my_mutex.try_lock()){};
            ad_information (robot,receive,rep);
             my_mutex.unlock();

             //THOMAS A TOI
        }

}


int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    QApp w;
//    w.show();

//    return a.exec();


    conf::SIZE_X = 3;
    conf::SIZE_Y = 4;
    Robot robot1;
    Robot robot2;
    robot1.id = 1;
    robot1.x = 0;
    robot1.y = 0;
    robot1.dir_scan = RIGHT;

    robot2.id = 2;
    robot2.x = 2;
    robot2.y = 2;
    robot2.dir_scan = LEFT;
    repr rep(conf::SIZE_X,conf::SIZE_Y);

    std::thread t1(Robot1,robot1,&rep);
    std::thread t2(Robot2,robot2,&rep);

     t1.join();
     t2.join();
     return 0;
}
