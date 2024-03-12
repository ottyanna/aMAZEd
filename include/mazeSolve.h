#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H // include guards

#include "maze.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void DFSsolve(Maze &, int);
bool DFSvisitSolve(Maze &, Vertex *);

#endif