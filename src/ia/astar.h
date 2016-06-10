#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <deque>
#include <stdlib.h>
#include "representation.h"
using namespace std;

struct Case {
        int x;
        int y;
        int coord;
        int F;
        int G;
        int H;
        Case *parent;
        int ancienne_direction;
};

bool be_ouvert (int x,int y);
bool be_ferme (int x,int y);
int return_indice (int x,int y);
int return_H (int x1, int x2);
void new_Case (int new_x, int  new_y, int ancienne_direction, int G_parent, int x_goal, int y_goal,Case *parent);
void return_ouvert (Case *courant,int x_goal, int y_goal,repr reper);
void direction_begin (Case *courant,int x_goal,int y_goal,repr reper,int largeur,int longueur);
void find_path_ricochet (int x_dep, int y_dep, int x_goal, int y_goal, int longueur, int largeur,repr reper);
Case lowest_node ();
#endif // ASTAR_H
