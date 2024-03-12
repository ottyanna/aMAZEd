#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"
#include "mazeGen.h"

using namespace std;

int main() {

  Maze m(10, 15); // width and height
  m.initGrid(0, 8);
  m.print();

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  DFSGen(m);

  drawMaze.join();
}
