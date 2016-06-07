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
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
};

#endif // GLOBAL_H
