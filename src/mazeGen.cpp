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

#include "mazeGen.h"

// DFS maze generation from a start vertex using an explicit stack
void RandomDFS(Maze &m, int start) {

  cout << "Generating maze with randomDFS with explicit stack data structure..."
       << endl
       << endl;

  stack<Vertex *> S;

  S.push(&m.vertices[start]);

  while (S.size() != 0) {

    this_thread::sleep_for(chrono::milliseconds(delayGen));

    Vertex *u = S.top();
    u->color = GREY;

    // temporary vector for not visited(=WHITE) adjacent vertex ids
    vector<int> adjWhiteIndex;
    adjWhiteIndex.reserve(4);

    for (int k = 0; k < m.adjList[u->id].size(); k++) {
      if (m.adjList[u->id][k].adjPtr->color == WHITE)
        adjWhiteIndex.push_back(k);
    }

    // choose a random available adjacent vertex
    if (adjWhiteIndex.size() != 0) {
      int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
      m.adjList[u->id][randIndex].adjPtr->parent = u;
      m.wallBreak(u->id, randIndex); // create the connection
      S.push(m.adjList[u->id][randIndex].adjPtr);
    } else {
      u->color = BLACK; // blacken u; it is finished
      S.pop();
    }
  }
}

// DFS maze generation from a start vertex using recursion
void DFSvisit(Maze &m, Vertex *u) {

  this_thread::sleep_for(chrono::milliseconds(delayGen));

  u->color = GREY;

  // temporary vector for not visited(=WHITE) adjacent vertex ids
  vector<int> adjWhiteIndex;
  adjWhiteIndex.reserve(4);

  for (int k = 0; k < m.adjList[u->id].size(); k++) {
    if (m.adjList[u->id][k].adjPtr->color == WHITE)
      adjWhiteIndex.push_back(k);
  }

  // choose a random available adjacent vertex
  if (adjWhiteIndex.size() != 0) {
    int randIndex = adjWhiteIndex[rand() % adjWhiteIndex.size()];
    m.adjList[u->id][randIndex].adjPtr->parent = u;
    m.wallBreak(u->id, randIndex); // create the connection
    DFSvisit(m, m.adjList[u->id][randIndex].adjPtr);
  } else {
    u->color = BLACK; // blacken u; it is finished
    if (u->parent != nullptr)
      DFSvisit(m, u->parent);
  }
}

void DFSGen(Maze &m, int start) {

  cout << "Generating maze with DFS..." << endl << endl;

  DFSvisit(m, &m.vertices[start]);
}
