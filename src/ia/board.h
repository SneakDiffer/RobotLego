/*=================================================
 *                   BOARD.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant la tableau de cases        *
 *================================================*/

#ifndef BOARD_H
#define BOARD_H
#include "case.h"
#include "global.h"

struct Board{
    Case* labyrinthe[SIZE_X][SIZE_Y];
};

#endif // BOARD_H

//CLASSE NON UTILISEE
