#ifndef POSIBILITIES_H
#define POSIBILITIES_H

/*=================================================
 *                 POSSIBILITIES.H                *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant les possibilitées de       *
 *              chemin possible                   *
 *================================================*/

//Classes Possibilities
class Posibilities{
    public:
        Posibilities();
        ~Posibilities();
        Path getBestPath();
        //Création des chemins
        void calculateAStarPath();
        void calculateAllRicochetPath();
    private:
        std::vector<Path*> p_listOfPath;
};


#endif // POSIBILITIES_H
