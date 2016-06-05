/*=================================================
 *                   BOARD.CPP                    *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.cpp contenant la tableau de cases      *
 *================================================*/

#include <iostream>
#include <vector>
#include "board.h"
#include "case.h"

//Constructeur
Board::Board(int rows, int cols)
: b_Rows(rows),
  b_Cols(cols)
{

}

 //Destructeur
 Board::~Board(){
 }

 //Méthodes

    Case* Board::getAt(int row, int col){
        return this->b_Data[row*col];
    }

