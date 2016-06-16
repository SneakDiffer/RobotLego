#ifndef ROBOT_H
#define ROBOT_H


struct Robot{
    int id;
    int x;
    int y;
    int dir;
    Robot(int _id,int _x,int _y,int _dir):id(_id),x(_x),y(_y),dir(_dir){}
    int dir_scan;
};

#endif // ROBOT_H
