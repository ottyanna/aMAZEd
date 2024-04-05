/*
 * aMAZEd is a C++ program that creates and solves mazes
 * Copyright (c) 2024 Anna Spanò
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mazeSolve.h"

// draws path following parents pointers
void drawPath(Maze &m, int index) {

  if (m.vertices[index].parent != nullptr &&
      m.vertices[index].parent->type != START) {
    m.vertices[index].parent->type = PATH;
    drawPath(m, m.vertices[index].parent->id);
  } else
    return;
}

/*A* SEARCH*/

// Manhattan Heuristic distance, good for grid with 4 possible moves
// d=|DeltaX|+|DeltaY|
int ManhattanHeuristic(Maze &m, Vertex u, int finish) {

  int deltaX = abs(u.id % m.nColumns - finish % m.nColumns);
  int deltaY = abs(u.id / m.nColumns - finish / m.nColumns);
  return deltaX + deltaY;
}

void AStarSolve(Maze &m, int start, int finish) {

  cout << "Solving maze with A*..." << endl << endl;

  m.resetMaze();
  m.vertices[start].g = 0;
  m.vertices[start].f = 0;
  // m.vertices[start].heuristicLengthToFinish; //+ g(start)

  // si può provare a non trovare il shortest e mettere
  // una tie breaking rule
  // int TieCounter = 0;

  MinHeap openHeap;

  m.vertices[start].color = GREY; // add the node to OPEN list
  m.vertices[start].handle = openHeap.push(&m.vertices[start]);

  while (!openHeap.empty()) {

    Vertex *u = openHeap.top();

    if (u->type == FINISH) {
      drawPath(m, u->id);
      // cout << "There were " << TieCounter << " ties!" << endl;
      return;
    }

    openHeap.pop();

    // if (!openHeap.empty())
    // if (openHeap.top()->f == u->f)
    // TieCounter++;

    this_thread::sleep_for(chrono::milliseconds(delaySolve));

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN) {

        int cost = u->g + v.weight;

        if (v.adjPtr->color == WHITE || cost < v.adjPtr->g) {
          v.adjPtr->g = cost;
          v.adjPtr->f = v.adjPtr->g + ManhattanHeuristic(m, *v.adjPtr, finish);
          v.adjPtr->parent = u;
          // not in the OPEN list ->
          // WHITE OR CLOSED==BLACK (if dist not consistent)
          if (v.adjPtr->color != GREY) {
            v.adjPtr->color = GREY;
            v.adjPtr->handle = openHeap.push(v.adjPtr);
          } else
            openHeap.update(v.adjPtr->handle); // it is already in the OPEN list
        }
      }
    }

    u->color = BLACK; // add the node to CLOSED list
  }
}

/*Depth First Search*/

bool DFSvisitSolve(Maze &m, Vertex *u) { // LIFO=Stack

  this_thread::sleep_for(chrono::milliseconds(delaySolve));

  u->color = GREY;

  if (u->type == FINISH) {
    drawPath(m, u->id);
    return true;
  }

  for (auto &v : m.adjList[u->id]) {
    if (v.adjPtr->color == WHITE && v.edgeType == OPEN) {
      v.adjPtr->parent = u;
      if (DFSvisitSolve(m, v.adjPtr))
        return true;
    }
  }

  u->color = BLACK;

  return false;
}

void DFSsolve(Maze &m, int start) {

  m.resetMaze();

  this_thread::sleep_for(chrono::milliseconds(delaySolve));

  cout << "Solving maze with DFS..." << endl << endl;

  if (DFSvisitSolve(m, &m.vertices[start]))
    return;
}

/*Breath First Search*/

void BFSsolve(Maze &m, int start) {

  m.resetMaze();

  this_thread::sleep_for(chrono::milliseconds(delaySolve));

  cout << "Solving maze with BFS..." << endl << endl;

  m.vertices[start].color = GREY;
  m.vertices[start].f = 0;

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
        this_thread::sleep_for(chrono::milliseconds(delaySolve));
        v.adjPtr->color = GREY;
        v.adjPtr->f = m.vertices[u].f + 1;
        Q.push(v.adjPtr->id);
      }
    }
    m.vertices[u].color = BLACK;
  }
}

/*DIJKSTRA*/

void DijkstraSolve(Maze &m, int start) {

  cout << "Solving maze with Dijkstra min heap..." << endl << endl;

  m.resetMaze();
  m.vertices[start].f = 0;

  MinHeap Q;

  for (auto &u : m.vertices) {
    u.handle = Q.push(&u);
  }

  while (!Q.empty()) {

    this_thread::sleep_for(chrono::milliseconds(delaySolve));

    Vertex *u = Q.top();
    Q.pop();

    u->color = BLACK;

    for (auto &v : m.adjList[u->id]) {
      if (v.edgeType == OPEN && v.adjPtr->color != BLACK &&
          v.adjPtr->f > v.weight + u->f) {
        this_thread::sleep_for(chrono::milliseconds(delaySolve));
        v.adjPtr->parent = u;
        v.adjPtr->f = u->f + v.weight;
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