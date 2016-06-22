#ifndef SQUAREEXPLORATION_H
#define SQUAREEXPLORATION_H

#include "representation.h"
#include "robot.h"

void simpleCase(Robot *robot, repr *maze, int x_goal, int y_goal);
void complexeCase(Robot *robot, repr *maze, int x_goal, int y_goal);

void squareExploration(Robot *robot, repr *maze, int x_goal, int y_goal);

int test_astar (repr* maze,Robot* robot,int x_goal, int y_goal);


#endif // SQUAREEXPLORATION_H
