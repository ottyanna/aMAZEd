#ifndef MAZE_H
#define MAZE_H // include guards

#include "vertex.h"
#include <iostream>
#include <vector>

using namespace std;

/* connectivity of vertices for a 2D grid as a adjacent matrix
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
*/

enum MazeEdgeType {

  WALL, // zero as in adjacency matrix zero means no connection
  OPEN

};

struct AdjListElem {

  Vertex *adjPtr;
  MazeEdgeType edgeType;
  int weight;

  AdjListElem(Vertex *_adjAdd);
  void print();
};

struct Maze {

  int nRows;
  int nColumns;
  vector<Vertex> vertices;
  vector<vector<AdjListElem>> adjList;

  Maze(int _nColumns, int _nRows);
  void initGrid(int start, int finish);
  void resetMaze();
  void print();
  void setWeight();
  void wallBreak(int, int);
  void addRandomLoops(int);
};

#endif