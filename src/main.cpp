#include <chrono>
#include <functional>
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

int main(int argc, char *argv[]) {

  if (argc == 1) {
    cout << "\nNo Extra Command Line Argument Passed "
            "Other Than Program Name"
         << endl;
    // return 0;
  }

  int start;
  int finish;

  if (argc != 1 && *argv[1] == 'a') { // gen+solve w/delay
    delayGen = 0;
    delaySolve = 1;

    Maze m(100, 100); // width and height
    start = 5050;
    finish = 0;
    m.initGrid(start, finish);

    srand(time(NULL));
    thread drawMaze(draw, ref(m));

    DFSGenNoRecursion(m, 0);
    m.addRandomLoops(1000);
    m.setWeight();

    AStarSolve(m, start, finish);

    drawMaze.join();

    return 0;
  }
  //
  // int start = 9999;
  // int finish = 250;
  //// start = 5000;
  // finish = 99;
  // finish = 0;
  // start = 3; //crisi dfs in 100x100
  // finish = 100;
  // start = 7000;
  // start = 3;
  finish = 90;
  start = 9000 + 90;
  start = 20100;
  finish = 200;

  Maze m(200, 200); // width and height
  // Maze m(180, 100);
  m.initGrid(0, finish);
  m.vertices[start].type = START;

  srand(time(NULL));
  thread drawMaze(draw, ref(m));

  Timer t;
  DFSGenNoRecursion(m, 0);
  cout << "maze generated in " << t.elapsed() << endl << endl;

  // m.addRandomLoops(3000); // dim/10
  m.addRandomLoops(10000);
  // m.print();
  m.setWeight();

  t.reset();
  DFSsolve(m, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(5000));

  t.reset();
  BFSsolve(m, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(5000));

  t.reset();
  AStarSolve(m, start, finish);
  cout << "maze solved in " << t.elapsed() << endl << endl;
  this_thread::sleep_for(chrono::milliseconds(5000));

  t.reset();
  DijkstraSolve(m, start);
  cout << "maze solved in " << t.elapsed() << endl << endl;

  cout << "Finished solving ";

  drawMaze.join();
}
