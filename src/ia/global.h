/*=================================================
 *                  GLOBAL.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant les informations globale   *
 *================================================*/


#ifndef GLOBAL_H_
#define GLOBAL_H_


/*================*
 *    DEFINES
 * ===============*/
//#define SIZE_X 23
//#define SIZE_Y 11
namespace conf {
    extern int SIZE_X;
    extern int SIZE_Y;
}


//Enum DIRECTION
enum Direction {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8

};

#endif // GLOBAL_H
