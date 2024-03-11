#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"

using namespace std;

int main() {

  cout << "hello";
  Maze m(3, 3); // width and height
  m.initGrid(0, 8);
  cout << "hello";
  m.print();

  srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze(draw, ref(m));

  drawMaze.join();
}
