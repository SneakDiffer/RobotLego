/*=================================================
 *                      PATH.H                    *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 *        Fichier.h contenant les chemins         *
 *================================================*/


#ifndef PATH_H
#define PATH_H
#include "path.h"
#include "pathelem.h"
#include <vector>

//Classe Path
class Path{
public:
    Path(); //Init lourde car on a (rows*cols)^4 possibilitées
    //Un peu moins avec les null
    ~Path();
    //Calculs:
    std::vector<Case*> AStar(Case* departure,Case* arrival);
    //Action:
    vois setWall(Case* c,int dir);//Fonction qui met un mur

private:
    //Liste de tout les PathElem
    std::vector<PathElem*> p_allPath;
};

#endif // PATH_H
