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

#ifndef MAZE_H
#define MAZE_H // include guards

#include "vertex.h"
#include <iostream>
#include <vector>

using namespace std;

/* connectivity of vertices for a 2D grid 4xN as a adjacent matrix
column index = adj
1 2 3 4 5 6 7 8 9 .....
. 1 . . 1 . . . . . . . 1 row index = node
1 . 1 . . 1 . . . . . . 2
. 1 . 1 . . 1 . . . . . 3
. . 1 . . . . 1 . . . . 4
1 . . . . 1 . . 1 . . .
. 1 . . 1 . 1 . . 1 . .
. . 1 . . 1 . 1 . . 1 .
. . . 1 . . 1 . . . . 1
. . . . 1 . . . . 1 . .
. . . . . 1 . . 1 . 1 .
. . . . . . 1 . . 1 . 1
. . . . . . . 1 . . 1 .

From this the adjacency list constructor (initGrid function) is easily computed
*/

// Type of edge
enum MazeEdgeType {

  WALL, // zero as in adjacency matrix zero means no connection
  OPEN  // there is a passage

};

// The element in the adjacent list
// `adjPtr` points to the adjacent Vertex
// `edgeType` tells if it is a WALL or it is OPEN passage
// `weight` is the weight of the edge
struct AdjListElem {

  Vertex *adjPtr;
  MazeEdgeType edgeType;
  int weight;

  AdjListElem(Vertex *_adjAdd);
  void print();
};

// Maze type
// `nRows` is the size of vertical dimension of the grid
// `nColumns` is the size of horizontal dimension of the grid
//`vertices` contains all the vertices with the respective fields
// `adjList` contains the adjacent list for the maze supposing the id of the
// vertices are ints from 0 to nRows*nColumns-1
struct Maze {

  int nRows;
  int nColumns;
  vector<Vertex> vertices;
  vector<vector<AdjListElem>> adjList;

  Maze(int _nColumns, int _nRows);
  void initGrid(int start, int finish);
  void wallBreak(int, int);
  void setWeight();

  void resetMaze();

  void addRandomLoops(int);

  void print();
};

#endif