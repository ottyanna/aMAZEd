#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H // include guards

#include "maze.h"
#include "vertex.h"
#include <algorithm>
#include <chrono>
#include <list>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

void drawPath(Maze &, int);
void DFSsolve(Maze &, int);
bool DFSvisitSolve(Maze &, Vertex *);
void BFSsolve(Maze &, int);
bool CompareVertexPointers(const Vertex *, const Vertex *);
void DijkstraSolve(Maze &, int);
void heuristicFunction(int, int);
void AStarSolve(Maze &, int, int);

#endif