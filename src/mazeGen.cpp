#include "mazeGen.h"

// DFS maze generation from a start vertex using an explicit stack
void RandomDFS(Maze &m, int start) {

  cout << "Generating maze with randomDFS with explicit stack data structure..."
       << endl
       << endl;

  stack<Vertex *> S;

  S.push(&m.vertices[start]);

  while (S.size() != 0) {

    this_thread::sleep_for(chrono::milliseconds(delayGen));

    Vertex *u = S.top();
    u->color = GREY;

    // temporary vector for not visited(=WHITE) adjacent vertex ids
    vector<int> adjWhiteIndex;
    adjWhiteIndex.reserve(4);

    for (int k = 0; k < m.adjList[u->id].size(); k++) {
      if (m.adjList[u->id][k].adjPtr->color == WHITE)
        adjWhiteIndex.push_back(k);
    }

    // choose a random available adjacent vertex
    if (adjWhiteIndex.size() != 0) {
      int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
      m.adjList[u->id][randIndex].adjPtr->parent = u;
      m.wallBreak(u->id, randIndex); // create the connection
      S.push(m.adjList[u->id][randIndex].adjPtr);
    } else {
      u->color = BLACK; // blacken u; it is finished
      S.pop();
    }
  }
}

// DFS maze generation from a start vertex using recursion
void DFSvisit(Maze &m, Vertex *u) {

  this_thread::sleep_for(chrono::milliseconds(delayGen));

  u->color = GREY;

  // temporary vector for not visited(=WHITE) adjacent vertex ids
  vector<int> adjWhiteIndex;
  adjWhiteIndex.reserve(4);

  for (int k = 0; k < m.adjList[u->id].size(); k++) {
    if (m.adjList[u->id][k].adjPtr->color == WHITE)
      adjWhiteIndex.push_back(k);
  }

  // choose a random available adjacent vertex
  if (adjWhiteIndex.size() != 0) {
    int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
    m.adjList[u->id][randIndex].adjPtr->parent = u;
    m.wallBreak(u->id, randIndex); // create the connection
    DFSvisit(m, m.adjList[u->id][randIndex].adjPtr);
  } else {
    u->color = BLACK; // blacken u; it is finished
    if (u->parent != nullptr)
      DFSvisit(m, u->parent);
  }
}

void DFSGen(Maze &m, int start) {

  cout << "Generating maze with DFS..." << endl << endl;

  DFSvisit(m, &m.vertices[start]);

  // TO REMOVE:
  // utile nel caso della foresta qui partiamo da start e non ci torniamo più
  // for (auto &u : m.vertices) {
  //   if (u.color == WHITE)
  //     DFSvisit(m, &u);
  // }
}
