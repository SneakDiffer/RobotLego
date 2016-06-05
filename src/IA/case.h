/*=================================================
 *                    CASE.H                      *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant une case du tableau        *
 *================================================*/

#ifndef CASE_H
#define CASE_H

//Classe Case
class Case{
    public:
        //Constructeur
        Case(int x, int y);
        //Getter
        int getx();
        int gety();
        bool getVisited();
        bool getUp();
        bool getDown();
        bool getLeft();
        bool getRight();
        //Setter
        void setVisited(bool v);
        void setUp(bool v);
        void setDown(bool v);
        void setLeft(bool v);
        void setRight(bool v);
        //Destructeur
        ~Case();
    private:
        int c_x;
        int c_y;
        bool c_visited;
        bool c_up;
        bool c_down;
        bool c_left;
        bool c_right;
};


#endif // CASE_H
