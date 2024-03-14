#include "mazeSolve.h"
#include "vertex.h"

void drawPath(Maze &m, int index) {

  if (m.vertices[index].parent != nullptr &&
      m.vertices[index].parent->type != START) {
    m.vertices[index].parent->type = PATH;
    drawPath(m, m.vertices[index].parent->id);
  } else
    return;
}

bool DFSvisitSolve(Maze &m, Vertex *u) { // LIFO=Stack

  // this_thread::sleep_for(chrono::milliseconds(100));

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

  this_thread::sleep_for(chrono::milliseconds(100));

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
        // this_thread::sleep_for(chrono::nanoseconds(1000));
        v.adjPtr->color = GREY;
        v.adjPtr->dist = m.vertices[u].dist + 1;
        v.adjPtr->parent = &m.vertices[u];
        Q.push(v.adjPtr->id);
      }
    }
    m.vertices[u].color = BLACK;
  }
}

// in Vertex.h non funziona
// comparison function or lambda
bool CompareVertexPointers(const Vertex *v1, const Vertex *v2) {

  return (v1->dist < v2->dist);
}

void DijkstraSolve(Maze &m,
                   int start) { // IPERSUPERLENTO SERVE IL MINHEAP REALE

  cout << "Solving maze with Dijkstra..." << endl << endl;

  m.resetMaze();
  m.setWeight();

  list<Vertex *> minHeap; // it should be a fibonacci heap
  m.vertices[start].dist = 0;

  for (auto &u : m.vertices) // bisogna sempre passarlo per referenza
    minHeap.push_back(&u);

  minHeap.sort(CompareVertexPointers);

  while (minHeap.size() != 0) {

    // this_thread::sleep_for(chrono::nanoseconds(1000));

    Vertex *u = minHeap.front();
    minHeap.pop_front();

    u->color = BLACK;

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN && v.adjPtr->color != BLACK &&
          v.adjPtr->dist > v.weight + u->dist) {
        // this_thread::sleep_for(chrono::milliseconds(1));
        v.adjPtr->parent = u;
        v.adjPtr->dist = u->dist + v.weight;
        v.adjPtr->color = GREY;
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
      }
    }

    minHeap.sort(CompareVertexPointers);
  }
}