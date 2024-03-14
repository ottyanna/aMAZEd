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

  int start = 4999;
  int finish = 0;

  Maze m(100, 100); // width and height
  m.initGrid(start, finish);

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  DFSGen(m, start);
  // m.print();
  DijkstraSolve(m, start);
  this_thread::sleep_for(chrono::milliseconds(1000));
  DFSsolve(m, start);

  drawMaze.join();
}
