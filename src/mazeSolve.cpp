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
        v.adjPtr->parent = &m.vertices[u];
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
        this_thread::sleep_for(chrono::milliseconds(delay));
        v.adjPtr->color = GREY;
        v.adjPtr->dist = m.vertices[u].dist + 1;
        Q.push(v.adjPtr->id);
      }
    }
    m.vertices[u].color = BLACK;
  }
}

void DijkstraSolve(Maze &m, int start) {

  cout << "Solving maze with Dijkstra min heap..." << endl << endl;

  m.resetMaze();
  m.setWeight();
  m.vertices[start].dist = 0;

  MinHeap Q;

  for (auto &u : m.vertices) // bisogna sempre passarlo per referenza
  {
    u.handle = Q.push(&u);
  }

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
        Q.update(v.adjPtr->handle);
        if (v.adjPtr->type == FINISH) {
          drawPath(m, v.adjPtr->id);
          return;
        }
      }
    }
  }
}

int ManhattanHeuristic(Maze &m, Vertex u, int finish) {

  int deltaX = abs(u.id % m.nColumns - finish % m.nColumns);
  int deltaY = abs(u.id / m.nColumns - finish / m.nColumns);
  return deltaX + deltaY;
}

// g è g
// f=dist
void AStarSolve(Maze &m, int start, int finish) {

  cout << "Solving maze with A* min heap..." << endl << endl;

  m.resetMaze();
  m.setWeight();
  m.vertices[start].g = 0;
  m.vertices[start].dist = 0;
  // m.vertices[start].heuristicLengthToFinish; //+ g(start)
  int TieCounter = 0; // si può provare a non trovare il shortest e mettere una
                      // tie breaking rule

  MinHeap openHeap;

  m.vertices[start].color = GREY; // add the node to OPEN list
  m.vertices[start].handle = openHeap.push(&m.vertices[start]);

  while (!openHeap.empty()) {

    Vertex *u = openHeap.top();

    if (u->type ==
        FINISH) { // prima di associare u do dopo? se top è O(1) meglio prima
      drawPath(m, u->id);
      cout << "There were " << TieCounter << " ties!" << endl;
      return;
    }

    openHeap.pop();

    if (!openHeap.empty())
      if (openHeap.top()->dist == u->dist)
        TieCounter++;

    // u->print();

    this_thread::sleep_for(chrono::milliseconds(delay));

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN) {

        int cost = u->g + v.weight;

        if (v.adjPtr->color == WHITE || cost < v.adjPtr->g) {
          v.adjPtr->g = cost;
          v.adjPtr->dist =
              v.adjPtr->g + ManhattanHeuristic(m, *v.adjPtr, finish);
          v.adjPtr->parent = u;
          if (v.adjPtr->color !=
              GREY) { // not in the open list quindi o bianco o closed
            v.adjPtr->color = GREY;
            v.adjPtr->handle = openHeap.push(v.adjPtr);
          } else
            openHeap.update(v.adjPtr->handle); // it is già in the open list
        }
      }
    }

    u->color = BLACK; // add the node to CLOSED list
  }
}
