/*=================================================
 *                  GLOBAL.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant les informations globale   *
 *================================================*/


#ifndef GLOBAL_H
#define GLOBAL_H


/*================*
 *    DEFINES
 * ===============*/
//#define SIZE_X 23
//#define SIZE_Y 11
namespace conf {
    int SIZE_X;
    int SIZE_Y;
};


//Enum DIRECTION
enum Direction {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8

};

#endif // GLOBAL_H
