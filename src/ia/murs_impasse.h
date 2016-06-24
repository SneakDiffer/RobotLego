#ifndef MURS_IMPASSE_H
#define MURS_IMPASSE_H
#include "representation.h"
#include "src/ia/connection.h"
#include "src/ia/wall_dir.h"
#include "src/ia/wall_dir_scan.h"
#include "src/ia/astar.h"


void direction_UP_murs_UP_1 (Robot* robot,repr* maze,int x_begin, int y_begin);


void direction_DOWN_murs_DOWN_2 (Robot* robot,repr* maze,int x_begin, int y_begin);

void direction_RIGHT_murs_RIGHT_3 (Robot* robot,repr* maze,int x_begin, int y_begin);


void direction_RIGHT_murs_RIGHT_4 (Robot* robot,repr* maze,int x_begin, int y_begin);


void direction_UP_murs_UP_5 (Robot* robot,repr* maze,int x_begin, int y_begin);

void direction_DOWN_murs_DOWN_6 (Robot* robot,repr* maze,int x_begin, int y_begin);

void direction_LEFT_murs_LEFT_7 (Robot* robot,repr* maze,int x_begin, int y_begin);

void direction_LEFT_murs_LEFT_8 (Robot* robot,repr* maze,int x_begin, int y_begin);


#endif // MURS_IMPASSE_H
