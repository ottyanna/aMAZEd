#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"
#include "mazeGen.h"
#include "mazeSolve.h"

using namespace std;

int main() {

  int start = 1520;
  int finish = 10;

  Maze m(100, 100); // width and height
  m.initGrid(start, finish);
  // m.print();

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  DFSGen(m, start);
  DFSsolve(m, start);

  drawMaze.join();
}
