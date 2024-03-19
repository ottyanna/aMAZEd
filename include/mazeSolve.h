#ifndef MAZE_SOLVE_H
#define MAZE_SOLVE_H // include guards

#include "maze.h"
#include "vertex.h"
#include <algorithm>
#include <boost/heap/binomial_heap.hpp>
#include <chrono>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

using namespace std;
using namespace boost::heap;

void drawPath(Maze &, int);
void DFSsolve(Maze &, int);
bool DFSvisitSolve(Maze &, Vertex *);
void BFSsolve(Maze &, int);
void DijkstraSolve(Maze &, int);
int ManhattanHeuristic(Maze &, Vertex, int);
void AStarSolve(Maze &, int, int);

#endif