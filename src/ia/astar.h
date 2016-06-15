#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <deque>
#include <stdlib.h>
#include "representation.h"
#include "connection.h"
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

int affiche_ouvert ();
int affiche_ferme ();
bool be_ouvert (int x, int y);
bool be_ferme (int x, int y);
int return_indice (int x,int y);
int return_H (int x1, int x2);
void new_Case (int new_x, int  new_y, int ancienne_direction, int G_parent, int x_goal, int y_goal,Case *parent);
void return_ouvert_not_ricochet (Case *courant,int x_goal, int y_goal,repr reper);
void return_ouvert_ricochet (Case *courant,int x_goal, int y_goal,repr reper);
void direction_begin (Case *courant,int x_goal,int y_goal,repr reper,int largeur,int longueur);
Case lowest_node ();
Case return_node (int x, int y);
void affiche_chemin (Case *courant,int x_dep, int y_dep);
void envoi_chemin(Robot robot);

//Les deux fonctions suivantes, envoie directement le chemin à suivre, return -1 si pas de chemin trouver, et 0 si chemin trouvé
int find_path_ricochet (int x_dep, int y_dep, int x_goal, int y_goal, int longueur, int largeur,repr reper,Robot robot);
int find_path_not_ricochet (int x_dep, int y_dep, int x_goal, int y_goal, repr reper,Robot robot);

#endif // ASTAR_H
