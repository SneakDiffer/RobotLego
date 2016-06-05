/*=================================================
 *                   PATHELEM.H                   *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 *      Fichier.h contenant les elements et       *
 *      informations sur une case d'un chemin     *
 *================================================*/

#ifndef PATHELEM_H
#define PATHELEM_H
#include "pathelem.h"
#include "case.h"

class PathElem{
public:
    PathElem(Case* actualCase,PathElem* previousCase,Case* depart);
    ~PathElem();
    //Getter
    Case* getCurentCase();
    int getF();
    int getH();
    int getG();
    PathElem* getPathElem(int dir);
    PathElem* getParent();

private:
    //Information des cases
    Case* value;
    PathElem* previous;
    Case* departure;
    //Information sur les voisins
    PathElem* up;
    PathElem* down;
    PathElem* left;
    PathElem* right;
    //Informations pour exploitation
    int G;  //Distance de la case départ à la case actuelle
    int H;  //Distance à vol d'oiseau entre courant et arrivé
    int F;  //G+H
};

#endif // PATHELEM_H
