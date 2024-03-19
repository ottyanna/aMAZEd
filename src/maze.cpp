#include "maze.h"

/*AdjListElement methods*/

// adds default adjacent element
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

/*Maze methods*/

// constructor of the Maze type
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

// creates "adjacency" list of a 2d grid of nRows*nColumns size without any real
// connection default is WALL for drawing purpose
void Maze::initGrid(int start, int finish) {

  vertices[start].type = START;
  vertices[finish].type = FINISH;

  // u is the index of the vertex
  for (int u = 0; u < vertices.size(); u++) {

    // There is a maximum of 4 possible ways to move around
    adjList[u].reserve(4);

    // delete the initialization -1 vertex
    adjList[u].pop_back();

    // AdjListElem(vertices[u]) inits the element of the list with WALL edge

    if ((u + 1) % nColumns != 0) { // I can move to the right
      adjList[u].push_back(AdjListElem(&vertices[u + 1]));
    }

    if (u + nColumns < vertices.size()) // I can move down
      adjList[u].push_back(AdjListElem(&vertices[u + nColumns]));

    if (u % nColumns != 0) { // I can move to the left
      adjList[u].push_back(AdjListElem(&vertices[u - 1]));
    }

    if (u - nColumns >= 0) // I can move up
      adjList[u].push_back(AdjListElem(&vertices[u - nColumns]));
  }
}

/* Sets the edgeType to OPEN, so it "creates" the connections */
void Maze::wallBreak(int indexVert, int indexAdj) {

  adjList[indexVert][indexAdj].edgeType = OPEN;

  // loop in the adjacency list of the adjacent element and "break" that
  // wall,too. Maybe there is a better way to use symmetry.
  int newIndex = adjList[indexVert][indexAdj].adjPtr->id;
  for (auto &u : adjList[newIndex]) { // TO REMOVE: att al &u!
    if (u.adjPtr->id == indexVert) {
      u.edgeType = OPEN;
      break;
    }
  }
}

// sets the weight of every edge in the graph, in the unweighted grid is 1 for
// every edge
void Maze::setWeight() {

  for (int k = 0; k < vertices.size(); k++) {
    for (auto &u : adjList[k])
      if (u.edgeType == OPEN)
        u.weight = 1;
  }
}

// resets all the relevant fields of the maze in order to have a fresh maze to
// be solved
void Maze::resetMaze() {

  for (auto &u : vertices) {
    u.color = WHITE;
    if (u.type == PATH)
      u.type = NONE;
    u.f = INF;
    u.parent = nullptr;
  }
}

// Adds some random loops to "spice up" the maze and make A* more evident
// by breaking some walls
void Maze::addRandomLoops(int maxLoop) {

  for (int k = 0; k < maxLoop; k++) {

    int randIndex = rand() % vertices.size();

    wallBreak(randIndex, 0); // always the first that exist always
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
