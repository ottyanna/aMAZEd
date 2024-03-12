#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"
#include "mazeGen.h"

using namespace std;

int main() {

  int start = 0;
  int finish = 8;

  Maze m(10, 10); // width and height
  m.initGrid(start, finish);
  m.print();

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  DFSGen(m, start);

  drawMaze.join();
}
