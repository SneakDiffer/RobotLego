#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include "deplacement.h"
#include "coord.h"
/*=================================================
 *                 DEPLACEMENT.H                  *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant les déplacement d'une case *
 *                à une autre                     *
 *================================================*/

//Classe Deplacement
class Deplacement{
    public:
        Deplacement(int dir);
        ~Deplacement();
        void setPossible(bool b);
        bool isPossible();
        void setG(int g);//Recalcule aussi F
        void setH(int h);//Recalcule aussi F
        int getG();
        int getH();
        int getF();
        int getDir();
    private:
        Coord d_caseDep;
        Coord d_caseArrival;
        bool d_possible;//si le déplacement est possible
        int d_G;// Distance depuis la case depart
        int d_H; // Distance relative
        int d_F; // F = G + H
        int d_dir;//direction
};


#endif // DEPLACEMENT_H
