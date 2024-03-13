#include "mazeSolve.h"
#include "vertex.h"
#include <algorithm>
#include <tuple>
#include <utility>

void drawPath(Maze &m, int index) {

  if (m.vertices[index].parent != nullptr &&
      m.vertices[index].parent->type != START) {
    m.vertices[index].parent->type = PATH;
    drawPath(m, m.vertices[index].parent->id);
  } else
    return;
}

bool DFSvisitSolve(Maze &m, Vertex *u) { // LIFO=Stack

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

void BFSsolve(Maze &m, int start) { // ma la distanza serve a noi???
                                    // forse posso fare altri type e dire dist
                                    // crescente da origine se voglio

  m.resetMaze(); // se li voglio assieme i path devo capire come fare.. tipo
                 // altro type a parte ...

  cout << "Solving maze with BFS..." << endl << endl;

  m.vertices[start].color = GREY;
  m.vertices[start].dist = 0;

  queue<int> Q;
  Q.push(start);

  while (Q.size() != 0) {
    int u = Q.front();
    Q.pop(); // FIFO =FIRST IN FIRST OUT
    for (auto v : m.adjList[u]) {
      if (v.adjPtr->color == WHITE && v.edgeType == OPEN) {
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
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

void DijkstraSolve(Maze &m, int start) { // bisogna inizializzare un peso da
                                         // qualche parte usare coloriii
  m.resetMaze();

  m.vertices[start].dist = 0;

  vector<pair<int, bool>> D; // in S bool=true;

  for (auto &u : m.adjList[start])
    if (u.edgeType == OPEN)
      u.adjPtr->dist = u.weight;

  for (auto u : m.vertices) {
    if (u.id != start)
      D.push_back(
          make_pair(u.dist, false)); // D[vertexId] is distance from 0 to
                                     // vertedId same index as m.vertices
    else
      D.push_back(make_pair(u.dist, true)); // true is the vertex in S
  }

  int sSize = 1;

  while (sSize != m.vertices.size()) {

    int min_indx = 0;

    while (!get<bool>(D[min_indx])) {
      min_indx++;
    }

    int startInd = min_indx;

    for (int k = startInd; k < D.size(); k++) {
      if (!get<bool>(D[k]))
        if (get<int>(D[k]) < get<int>(D[min_indx]))
          min_indx = k; // w
    }

    D[min_indx].second = true; // lo aggiungo a S
    // put parent uguale a quello prima
    sSize++;

    int SuppDw = D[min_indx].first; ////????????

    for (auto &u : m.adjList[min_indx])
      if (u.edgeType == OPEN)
        u.adjPtr->dist = 1 + SuppDw;

    for (int k = 0; k)
  }
}

void DijkstraSolve(Maze &m, int start) { // bisogna inizializzare un peso da
                                         // qualche parte usare coloriii
  m.resetMaze();
  m.setWeight();

  m.vertices[start].dist = 0;
  m.vertices[start].color = BLACK;

  for (auto &u : m.adjList[start]) {
    if (u.edgeType == OPEN)
      u.adjPtr->dist = min(u.adjPtr->dist, 1);
  }
}