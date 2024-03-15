#include "mazeGen.h"

void DFSGenNoRecursion(
    Maze &m,
    int start) { // lo stack fa le veci del for e chiamata di ricorsione

  cout << "Generating maze with DFS with stack data structure..." << endl
       << endl;

  stack<Vertex *> S;

  S.push(&m.vertices[start]);

  while (S.size() != 0) {

    // his_thread::sleep_for(chrono::milliseconds(1));

    Vertex *u = S.top();
    u->color = GREY;

    vector<int> adjWhiteIndex; // vettore di supporto per gli indici di quelli
                               // white

    for (int k = 0; k < m.adjList[u->id].size(); k++) {
      if (m.adjList[u->id][k].adjPtr->color == WHITE)
        adjWhiteIndex.push_back(k);
    }

    if (adjWhiteIndex.size() != 0) {
      int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
      m.adjList[u->id][randIndex].adjPtr->parent = u;
      m.wallBreak(u->id, randIndex);
      S.push(m.adjList[u->id][randIndex].adjPtr);
    } else {
      u->color = BLACK; // blacken u; it is finished
      S.pop();
    }
  }
}

void DFSvisit(Maze &m, Vertex *u) {

  // this_thread::sleep_for(chrono::milliseconds(1));

  u->color = GREY;

  vector<int> adjWhiteIndex; // vettore di supporto per gli indici di quelli
                             // white

  for (int k = 0; k < m.adjList[u->id].size(); k++) {
    if (m.adjList[u->id][k].adjPtr->color == WHITE)
      adjWhiteIndex.push_back(k);
  }

  if (adjWhiteIndex.size() != 0) {
    int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
    m.adjList[u->id][randIndex].adjPtr->parent = u;
    m.wallBreak(u->id, randIndex);
    DFSvisit(m, m.adjList[u->id][randIndex].adjPtr);
  } else {
    u->color = BLACK; // blacken u; it is finished
    if (u->parent != nullptr)
      DFSvisit(m, u->parent);
  }
}

void DFSGen(Maze &m, int start) { // devo farlo partire dallo start

  cout << "Generating maze with DFS..." << endl << endl;

  DFSvisit(m, &m.vertices[start]);

  // utile nel caso della foresta qui partiamo da start e non ci torniamo più
  // for (auto &u : m.vertices) {
  //   if (u.color == WHITE)
  //     DFSvisit(m, &u);
  // }
}
