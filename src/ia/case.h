/*=================================================
 *                    CASE.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant une case du tableau        *
 *================================================*/

#ifndef CASE_H
#define CASE_H

//Structure Case
struct Case{
    int x;
    int y;
    bool visited;
    Case* up;
    Case* down;
    Case* left;
    Case* right;
};


#endif
//CLASSE NON UTILISEE
