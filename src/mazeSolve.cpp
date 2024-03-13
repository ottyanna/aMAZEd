#include "mazeSolve.h"

void drawPath(Maze &m, int index) {

  if (m.vertices[index].parent != nullptr &&
      m.vertices[index].parent->type != START) {
    m.vertices[index].parent->type = PATHDFS;
    drawPath(m, m.vertices[index].parent->id);
  } else
    return;
}

bool DFSvisitSolve(Maze &m, Vertex *u) {

  this_thread::sleep_for(chrono::milliseconds(1));

  u->color = GREY;

  if (u->type == FINISH) {
    drawPath(m, u->id);
    return true;
  }

  for (auto &v : m.adjList[u->id]) {
    if (v.adjPtr->color == WHITE && v.edgeType == OPEN) {
      v.adjPtr->parent = u;
      if (DFSvisitSolve(
              m, v.adjPtr)) // se ha trovato il finish continua a ritornare true
        return true;
    }
  }

  u->color = BLACK;

  return false;
}

void DFSsolve(Maze &m, int start) { // devo farlo partire dallo start

  m.resetMaze();

  cout << "Solving maze with DFS..." << endl << endl;

  if (DFSvisitSolve(m, &m.vertices[start]))
    return;
}

void BFSsolve(Maze &m, int start) { // SERVE IL BACKTRACKINGGG

  m.resetMaze(); // se li voglio assieme i path devo capire come fare.. tipo
                 // altro type a parte ...

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
