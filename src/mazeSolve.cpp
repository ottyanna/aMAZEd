#include "mazeSolve.h"

int delay = 0;

void drawPath(Maze &m, int index) {

  if (m.vertices[index].parent != nullptr &&
      m.vertices[index].parent->type != START) {
    m.vertices[index].parent->type = PATH;
    drawPath(m, m.vertices[index].parent->id);
  } else
    return;
}

bool DFSvisitSolve(Maze &m, Vertex *u) { // LIFO=Stack

  this_thread::sleep_for(chrono::milliseconds(delay));

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

  this_thread::sleep_for(chrono::milliseconds(delay));

  cout << "Solving maze with DFS..." << endl << endl;

  if (DFSvisitSolve(m, &m.vertices[start]))
    return;
}

void BFSsolve(Maze &m, int start) { // ma la distanza serve a noi???
                                    // forse posso fare altri type e dire dist
                                    // crescente da origine se voglio

  m.resetMaze(); // se li voglio assieme i path devo capire come fare.. tipo
                 // altro type a parte ...

  this_thread::sleep_for(chrono::milliseconds(delay));

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
        this_thread::sleep_for(chrono::milliseconds(delay));
        v.adjPtr->color = GREY;
        v.adjPtr->dist = m.vertices[u].dist + 1;
        v.adjPtr->parent = &m.vertices[u];
        Q.push(v.adjPtr->id);
      }
    }
    m.vertices[u].color = BLACK;
  }
}

// functor to compare Vertex* as a min heap so the funct needs to invert the
// sign
struct CompareVertexPointersStruct {
  bool operator()(const Vertex *v1, const Vertex *v2) const {

    return (v1->dist > v2->dist);
  }
};

void DijkstraSolve(Maze &m, int start) {

  cout << "Solving maze with Dijkstra min heap..." << endl << endl;

  m.resetMaze();
  m.setWeight();
  m.vertices[start].dist = 0;

  using MinHeap = binomial_heap<Vertex *, compare<CompareVertexPointersStruct>>;

  MinHeap Q;
  vector<MinHeap::handle_type> handles;

  for (auto &u : m.vertices) // bisogna sempre passarlo per referenza
    handles.push_back(Q.push(&u));

  while (!Q.empty()) {

    this_thread::sleep_for(chrono::milliseconds(delay));

    Vertex *u = Q.top();
    Q.pop();

    u->color = BLACK;

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN && v.adjPtr->color != BLACK &&
          v.adjPtr->dist > v.weight + u->dist) {
        this_thread::sleep_for(chrono::milliseconds(delay));
        v.adjPtr->parent = u;
        v.adjPtr->dist = u->dist + v.weight;
        v.adjPtr->color = GREY;
        Q.update(handles[v.adjPtr->id]);
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
      }
    }
  }
}

void ManhattanHeuristic(Maze &m, int finish) {

  for (auto &u : m.vertices) {
    int deltaX = abs(u.id % m.nColumns - finish % m.nColumns);
    int deltaY = abs(u.id / m.nColumns - finish / m.nColumns);
    u.heuristicLengthToFinish = deltaX + deltaY;
  }
}

void EuclideanHeuristic(Maze &m, int finish) {

  for (auto &u : m.vertices) {
    int deltaX = pow(u.id % m.nColumns - finish % m.nColumns, 2);
    int deltaY = pow(u.id / m.nColumns - finish / m.nColumns, 2);
    u.heuristicLengthToFinish = pow(deltaX + deltaY, 0.5);
  }
}

void AStarSolve(Maze &m, int start, int finish) {

  cout << "Solving maze with A* min heap..." << endl << endl;

  m.resetMaze();
  m.setWeight();
  m.vertices[start].dist = 0;
  EuclideanHeuristic(m, finish);

  using MinHeap = binomial_heap<Vertex *, compare<CompareVertexPointersStruct>>;

  MinHeap Q;
  vector<MinHeap::handle_type> handles;

  for (auto &u : m.vertices) // bisogna sempre passarlo per referenza
    handles.push_back(Q.push(&u));

  while (!Q.empty()) {

    this_thread::sleep_for(chrono::milliseconds(delay));

    Vertex *u = Q.top();
    Q.pop();

    u->color = BLACK;

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN && v.adjPtr->color != BLACK &&
          v.adjPtr->dist >
              v.weight + u->dist + v.adjPtr->heuristicLengthToFinish) {
        this_thread::sleep_for(chrono::milliseconds(delay));
        v.adjPtr->parent = u;
        v.adjPtr->dist =
            u->dist + v.weight + v.adjPtr->heuristicLengthToFinish; ///???
        v.adjPtr->color = GREY;
        Q.update(handles[v.adjPtr->id]);
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
      }
    }
  }
}