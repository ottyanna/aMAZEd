#include "maze.h"
#include "vertex.h"
#include <iostream>

AdjListElem::AdjListElem(Vertex *_adjAdd) {
  adjPtr = _adjAdd;
  edgeType = WALL; // in the beginning no node is connected
}

void AdjListElem::print() {

  cout << endl;
  cout << "Adj Vert attributes i=" << adjPtr->id << " ";
  cout << "color=" << adjPtr->color << " ";
  cout << "type=" << adjPtr->type << " " << endl;
  cout << "Wall type is (0 wall, 1 open) " << edgeType << endl;
  cout << "-----" << endl;
}

Maze::Maze(int _nColumns, int _nRows) {

  nRows = _nRows;
  nColumns = _nColumns;

  vector<AdjListElem> v;
  //-1 is not a vertex, sentinel value(is this the right word?)
  Vertex vertSent(-1);
  v.push_back(AdjListElem(&vertSent));

  // reserve space for the exact amount of vertices
  vertices.reserve(nRows * nColumns);
  adjList.reserve(nRows * nColumns);

  for (int i = 0; i < nColumns * nRows; i++) {
    vertices.push_back(Vertex(i));
    adjList.push_back(v); // init the vector of AdjListElems with sentinel value
  }
}

// creates "adjacency" list of a 2d grid
void Maze::initGrid(int start,
                    int finish) { // nodefault per sizeC?? //start e finish come
                                  // li uso nel ptr???
  vertices[start].type = START;
  vertices[finish].type = FINISH;

  // u is the index of the vertex
  for (int u = 0; u < vertices.size(); u++) {

    // There is a maximum of 4 possible ways to move around
    adjList[u].reserve(4);

    // delete the initialization -1 vertex
    adjList[u].pop_back();

    // AdjListElem(vertices[u]) inits the WALL

    if ((u + 1) % nColumns != 0) { // I can move to the right
      adjList[u].push_back(AdjListElem(&vertices[u + 1])); // adiacenti a destra
    }

    if (u + nColumns < vertices.size())
      adjList[u].push_back(
          AdjListElem(&vertices[u + nColumns])); // adiacenti giù

    if (u % nColumns != 0) { // I can move to the left
      adjList[u].push_back(AdjListElem(&vertices[u - 1])); // adiacenti a sx
    }

    if (u - nColumns >= 0)
      adjList[u].push_back(
          AdjListElem(&vertices[u - nColumns])); // adiacenti su
  }
}

void Maze::resetMaze() {

  for (auto &u : vertices) {
    u.color = WHITE;
    if (u.type == PATH)
      u.type = NONE;
    u.dist = INF;
    u.parent = nullptr; //?
  }
}

void Maze::print() {

  cout << "Printing maze of " << nColumns << "x" << nRows << endl;

  cout << "vertices list is: " << endl;
  for (auto elem : vertices) {
    elem.print();
    cout << endl;
  }
  cout << endl;

  cout << "****";
  cout << endl << "adjacency list with wall tracking" << endl;
  int k = 0;
  for (auto v : adjList) {
    cout << k << ":" << endl;
    for (auto elem : v)
      elem.print();
    cout << endl;
    k++;
  }

  cout << endl;
}

void Maze::setWeight() {

  for (int k = 0; k < vertices.size(); k++) {
    for (auto &u : adjList[k])
      if (u.edgeType == OPEN)
        u.weight = 1;
  }
}

void Maze::wallBreak(int indexVert, int indexAdj) {

  adjList[indexVert][indexAdj].edgeType = OPEN;

  int newIndex = adjList[indexVert][indexAdj].adjPtr->id;
  for (auto &u : adjList[newIndex]) { // cicla nella lista di adiacenza
    // dell'adiacente e rompi pure quel muro
    // att al &u!! se no usa il copy constructor
    if (u.adjPtr->id == indexVert) {
      u.edgeType = OPEN;
      break;
    }
  }
}

void Maze::addRandomLoops(int maxLoop) {

  for (int k = 0; k < maxLoop; k++) {

    int randIndex = rand() % vertices.size();

    wallBreak(randIndex, 0); // always the first that exist always
  }
}
