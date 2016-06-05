/*=================================================
 *                   BOARD.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant la tableau de cases        *
 *================================================*/

#ifndef BOARD_H
#define BOARD_H
#include "case.h"
#include <vector>

//Classe  Board
class Board
{
public:
    Board(int rows, int cols);
    ~Board();
    Case* getAt(int row, int col);

private:
    int b_Rows;
    int b_Cols;
    std::vector<Case*> b_Data;
};

#endif // BOARD_H
