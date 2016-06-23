#ifndef WALL_DIR_H
#define WALL_DIR_H

#include "representation.h"

//On rempli la structure reper en fonction de la direction courante du robot !

void completement_ad_information_dir (Robot *robot, repr *reper, int nb_case, bool inverse);
void wall_visited_dir (Robot robot,repr *reper,int nb_case);
void ad_information_dir (Robot *robot, int distance, repr* reper);
void affiche_lab (repr* reper,int x, int y, int dir);

#endif // WALL_DIR_H
