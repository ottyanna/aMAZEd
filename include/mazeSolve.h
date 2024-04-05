/*
 * aMAZEd is a C++ program that creates and solves mazes
 * Copyright (c) 2024 Anna Spanò
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

int delaySolve = 0;

void drawPath(Maze &, int);

int ManhattanHeuristic(Maze &m, Vertex u, int finishID);
void AStarSolve(Maze &m, int start, int finish);

bool DFSvisitSolve(Maze &, Vertex *);
void DFSsolve(Maze &, int);

void BFSsolve(Maze &, int);

void DijkstraSolve(Maze &, int);

#endif