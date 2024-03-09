#ifndef MAZE_H
#define MAZE_H // include guards

#include <iostream>
#include <vector>

using namespace std;

enum MazeEdgeType {

  WALL, // zero as in adjacency matrix zero means no connection
  OPEN

};

/*
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

// Formato COO
struct EdgeAdjMatrix {

  int node;
  int adj;
  MazeEdgeType edgeType;

  EdgeAdjMatrix(int _node, int _adj) {
    node = _node;
    adj = _adj;
    edgeType = WALL; // in the beginning no node is connected
  }

  void print();
};

struct Maze {

  int rows;
  int columns;
  vector<EdgeAdjMatrix> adjMatrix;
  // manca vett di puntatori a nodi

  void initGrid(int, int, int, int);
  void print();
};

#endif