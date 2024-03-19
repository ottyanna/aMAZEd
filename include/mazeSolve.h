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

int ManhattanHeuristic(Maze &m, Vertex u, int finishID);
void AStarSolve(Maze &m, int start, int finish);

bool DFSvisitSolve(Maze &, Vertex *);
void DFSsolve(Maze &, int);

void BFSsolve(Maze &, int);

void DijkstraSolve(Maze &, int);

#endif