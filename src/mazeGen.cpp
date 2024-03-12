#include "mazeGen.h"
#include "maze.h"
#include "vertex.h"

void wallBreak(Maze &m, int indexVert, int indexAdj) {

  cout << "ANOTHER BREAK IN THE WALL " << endl << endl;

  // cout << "*********" << endl;
  //
  // m.print();
  //
  // cout << "***" << endl;

  cout << "breaking wall between " << indexVert << " and "
       << m.adjList[indexVert][indexAdj].adjPtr->id << endl;
  m.adjList[indexVert][indexAdj].edgeType = OPEN;
  // if (m.vertices[indexVert].parent != nullptr)
  //  cout << m.vertices[indexVert].parent->id << endl;

  int newIndex = m.adjList[indexVert][indexAdj].adjPtr->id;
  cout << "exploring adj = " << newIndex << endl;
  for (auto &u : m.adjList[newIndex]) { // cicla nella lista di adiacenza
    // dell'adiacente e rompi pure quel muro
    // att al &u!! se no usa il copy constructor
    u.print();
    if (u.adjPtr->id == indexVert) {
      cout << "breaking wall between "
           << m.adjList[indexVert][indexAdj].adjPtr->id << " and "
           << u.adjPtr->id << endl;
      cout << u.edgeType << endl;
      u.edgeType = OPEN;
      cout << u.edgeType << endl;
      // break;
    }
  }
  cout << "STOP THE BREAK" << endl;
}

void DFSvisit(Maze &m, Vertex *u) {

  this_thread::sleep_for(chrono::milliseconds(100));

  u->color = GREY;

  cout << "(u_Id : " << u->id << " and color " << u->color;
  if (u->parent != nullptr)
    cout << " and parent " << u->parent->id;
  cout << endl;

  vector<int> adjWhiteIndex; // vettore di supporto per gli indici di quelli
                             // white

  for (int k = 0; k < m.adjList[u->id].size(); k++) {
    if (m.adjList[u->id][k].adjPtr->color == WHITE)
      adjWhiteIndex.push_back(k);
  }

  if (adjWhiteIndex.size() != 0) {
    int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
    // cout << "randIndex " << randIndex << " with id "
    //     << m.adjList[u->id][randIndex].adjPtr->id << endl;
    m.adjList[u->id][randIndex].adjPtr->parent = u;
    wallBreak(m, u->id, randIndex);
    DFSvisit(m, m.adjList[u->id][randIndex].adjPtr);
  } else {
    u->color = BLACK; // blacken u; it is finished
    cout << u->id << " )";
    if (u->parent != nullptr)
      DFSvisit(m, u->parent);
  }
}

void DFSGen(Maze &m, int start) { // devo farlo partire dallo start

  cout << "Generating maze..." << endl << endl;

  DFSvisit(m, &m.vertices[start]);

  // utile nel caso della foresta qui partiamo da start e non ci torniamo più
  // for (auto &u : m.vertices) {
  //   if (u.color == WHITE)
  //     DFSvisit(m, &u);
  // }
}
