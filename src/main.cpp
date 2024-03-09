#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"

using namespace std;

int main() {

  Maze m;
  m.initGrid(0, 8, 3, 10);
  m.print();

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  cout << "hello world";

  drawMaze.join();
}
