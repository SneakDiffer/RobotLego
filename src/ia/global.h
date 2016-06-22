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



#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

#endif // GLOBAL_H
