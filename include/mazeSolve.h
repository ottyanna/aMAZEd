#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H // include guards

#include "maze.h"
#include <algorithm>
#include <chrono>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

void drawPath(Maze &, int);
void DFSsolve(Maze &, int);
bool DFSvisitSolve(Maze &, Vertex *);
void BFSsolve(Maze &, int);
void DijkstraSolve(Maze &, int);

#endif