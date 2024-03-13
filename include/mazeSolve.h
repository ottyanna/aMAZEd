#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H // include guards

#include "maze.h"
#include <chrono>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

void drawPath(Maze &, int);
void DFSsolve(Maze &, int);
bool DFSvisitSolve(Maze &, Vertex *);
void BFSsolve(Maze &, int);

#endif