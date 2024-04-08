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

#ifndef MAZE_GEN_H
#define MAZE_GEN_H // include guards

#include "maze.h"
#include <chrono>
#include <stack>
#include <thread>
#include <vector>

using namespace std;

static int delayGen = 0; // delay in milliseconds

void RandomDFS(Maze &, int);
void DFSGen(Maze &, int);
void DFSvisit(Maze &, Vertex *);

#endif
