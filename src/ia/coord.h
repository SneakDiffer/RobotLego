#ifndef COORD_H
#define COORD_H

/*=================================================
 *                   COORD.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant la classe coordonées       *
 *================================================*/

//Classe Coord
class Coord{
    public:
        Coord(int x,int y);
        ~Coord();
        int getx();
        int gety();
        void setx(int x);
        void sety(int y);
    private:
        int c_x;
        int c_y;
};

#endif // COORD_H
