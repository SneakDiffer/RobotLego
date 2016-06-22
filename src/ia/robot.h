#ifndef ROBOT_H
#define ROBOT_H


struct Robot{
    int id;
    int x;
    int y;
    int dir;
    int dir_scan;
    Robot(int _id,int _x,int _y,int _dir,int _dir_scan):id(_id),x(_x),y(_y),dir(_dir),dir_scan(_dir_scan){}
};

#endif // ROBOT_H
