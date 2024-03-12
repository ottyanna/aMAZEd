#include "mazeSolve.h"

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
