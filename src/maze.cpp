#include "maze.h"

void Maze::initGrid(int start, int finish, int sizeR,
                    int sizeC) { // nodefault per sizeC?? //start e finish come
                                 // li uso nel ptr???
  rows = sizeR;
  columns = sizeC;

  // reserve space for the exact amount of symmetric edge
  adjMatrix.reserve(sizeR * (sizeC - 1) + sizeC * (sizeR - 1));

  // for the symmetric property is like going only to the right and down
  for (int u = 0; u < sizeC * sizeR; u++) {
    if ((u + 1) % sizeC != 0) { // cond non sono sul lato dx
      adjMatrix.push_back(
          EdgeAdjMatrix(u, u + 1)); // adiacenti destra e sinistra
    }
    if (u + sizeC < sizeC * sizeR)
      adjMatrix.push_back(EdgeAdjMatrix(u, u + sizeC)); // adiacenti giù e su
  }
}

void EdgeAdjMatrix::print() {

  cout << endl;
  cout << this->node << " ";
  cout << this->adj << " ";
  cout << this->edgeType;
  cout << "-----" << endl;
}

void Maze::print() {

  for (auto elem : adjMatrix)
    elem.print();

  cout << endl;
  cout << adjMatrix.size();
}