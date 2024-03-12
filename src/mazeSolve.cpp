#include "mazeSolve.h"
#include "vertex.h"

bool DFSvisitSolve(Maze &m, Vertex *u) {

  this_thread::sleep_for(chrono::milliseconds(1));

  u->color = GREY;

  if (u->type == FINISH)
    return true;

  for (auto &v : m.adjList[u->id]) {
    if (v.adjPtr->color == WHITE && v.edgeType == OPEN) {
      v.adjPtr->parent = u;
      if (DFSvisitSolve(m, v.adjPtr))
        return true;
    }
  }

  u->color = BLACK; // blacken u; it is finished
  if (u->parent != nullptr)
    if (DFSvisitSolve(m, u->parent))
      return true;

  return true; // al punto ci dovrebbe arrivare sempre
}

void DFSsolve(Maze &m, int start) { // devo farlo partire dallo start

  m.resetMaze();

  cout << "Solving maze with DFS..." << endl << endl;

  if (DFSvisitSolve(m, &m.vertices[start]))
    return;
}

void BFSsolve(Maze &m, int start) { // SERVE IL BACKTRACKINGGG

  m.resetMaze();

  cout << "Solving maze with BFS..." << endl << endl;

  m.vertices[start].color = GREY;
  m.vertices[start].dist = 0;

  queue<int> Q;
  Q.push(start);

  while (Q.size() != 0) {
    int u = Q.back();
    Q.pop(); // cambiare nomi a u e v
    for (auto v : m.adjList[u]) {
      if (v.adjPtr->color == WHITE && v.edgeType == OPEN) {
        this_thread::sleep_for(chrono::milliseconds(1));
        v.adjPtr->color = GREY;
        v.adjPtr->dist = m.vertices[u].dist + 1;
        v.adjPtr->parent = &m.vertices[u];
        Q.push(v.adjPtr->id);
      }
    }
    m.vertices[u].color = BLACK;
  }
}
