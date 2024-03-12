#ifndef MAZE_GEN_H
#define MAZE_GEN_H // include guards

#include "maze.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

void DFSGen(Maze &, int);
void DFSvisit(Maze &, Vertex *);

#endif