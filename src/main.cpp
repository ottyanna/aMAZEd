#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"
#include "mazeGen.h"
#include "mazeSolve.h"

using namespace std;

/**
 * @brief Timer class to easily time code execution
 * Highly inspired (if not entirely copied) from
 * https://www.learncpp.com/cpp-tutorial/timing-your-code/
 *
 */
struct Timer {
private:
  // Type aliases to make accessing nested type easier
  using clock_t = chrono::high_resolution_clock;
  using second_t = chrono::duration<double, ratio<1>>;

  chrono::time_point<clock_t> m_beg;

public:
  /**
   * @brief Construct a new Timer object with the time of calling
   *
   */
  Timer() : m_beg{clock_t::now()} {}
  /**
   * @brief Resets the timer
   *
   */
  void reset() { m_beg = clock_t::now(); }

  /**
   * @brief Returns the elapsed time in proper units
   *
   * @return double
   */
  double elapsed() const {
    return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
  }
};

int main() {

  int start = 9999;
  int finish = 20;

  Maze m1(100, 100); // width and height
  m1.initGrid(start, finish);

  Maze m(100, 100); // width and height
  m.initGrid(start, finish);

  /* Initialize the library */
  if (!glfwInit())
    return -1;
  GLFWwindow *window1 =
      glfwCreateWindow(500, 500, "Maze Solver 1 ", NULL, NULL);
  GLFWwindow *window2 =
      glfwCreateWindow(500, 500, "Maze Solver 2 ", NULL, NULL);
  if (!window1 || !window2) {
    glfwTerminate();
    return -1;
  }

  srand(10);
  // srand(time(NULL));

  // red is right hand
  // yellow is a*
  thread drawMaze1(draw, ref(m), window1);
  thread drawMaze2(draw, ref(m1), window2);
  Timer t;
  DFSGenNoRecursion(m, 0);
  m.addRandomLoops(1000); // dim/10
  DFSGenNoRecursion(m1, 0);
  m1.addRandomLoops(1000); // dim/10
  // m.print();
  cout << "maze generated in " << t.elapsed() << endl << endl;
  t.reset();
  AStarSolve(m, start, finish);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  t.reset();

  cout << "second thread" << endl;

  DijkstraSolve(m, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  t.reset();
  DFSsolve(m1, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  t.reset();
  BFSsolve(m, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;

  drawMaze1.join();
  drawMaze2.join();

  return 0;
}
