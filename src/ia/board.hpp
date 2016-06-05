#ifndef BOARD_H
#define BOARD_H
#include <vector>

/*=================================================
 *                   BOARD.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant la tableau de cases        *
 *================================================*/

//Classe  Board
class Board{
    public:
        Board(int row, int col);
        Case getCaseAt(int row,int col);
        Case getCaseAt(Coord c);
        ~Board();
    private:
        int b_nbRow;
        int b_nbCol;
        Case** b_board;// Matrice 2D
};

#endif 
