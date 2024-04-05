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

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "draw.h"
#include "maze.h"
#include "mazeGen.h"
#include "mazeSolve.h"
#include "vertex.h"

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
    return 0;
  }

  int delayInBetween = 0;
  int start;
  int finish;
  srand(time(NULL)); // initialize seed for maze generation

  if (argc != 1 && *argv[1] == '0') { // just plain generation
    delayGen = 0;
    delayInBetween = 5000;

    start = 1000;
    finish = 0;
    Maze m(50, 50);
    m.initGrid(start, finish);
    m.vertices[start].type = NONE;
    m.vertices[finish].type = NONE;

    thread drawMaze(draw, ref(m));

    RandomDFS(m, 0);
    m.resetMaze();
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));
    m.addRandomLoops(1000);

    drawMaze.join();

    return 0;
  }

  if (argc != 1 && *argv[1] == 'a') { // gen+solve w/delay
    delayGen = 1;
    delaySolve = 1;

    Maze m(50, 50);
    start = 1025;
    finish = 3;
    m.initGrid(start, finish);

    thread drawMaze(draw, ref(m));

    RandomDFS(m, 0);
    m.addRandomLoops(1000);
    m.setWeight();

    AStarSolve(m, start, finish);

    cout << "finished solving" << endl;

    drawMaze.join();

    return 0;
  }

  else if (argc != 1 && *argv[1] == 'b') { // solve DFS+BFS+Dijkstra+A*

    delayInBetween = 5000;
    delayGen = 0;
    delaySolve = 0;

    Maze m(180, 100); // width and height
    start = 9090;
    finish = 90;
    m.initGrid(start, finish);

    thread drawMaze(draw, ref(m));

    Timer t;
    RandomDFS(m, 0);
    cout << "maze generated in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    m.addRandomLoops(5000);
    m.setWeight();

    t.reset();
    DFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    BFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    DijkstraSolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    AStarSolve(m, start, finish);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    cout << "finished solving" << endl;

    drawMaze.join();

    return 0;
  }

  else if (argc != 1 &&
           *argv[1] == 'c') { // solve DFS+BFS+Dijkstra+A* just time

    delayInBetween = 0;
    delayGen = 0;
    delaySolve = 0;

    Maze m(180, 100); // width and height
    start = 9090;
    finish = 90;
    m.initGrid(start, finish);

    Timer t;
    RandomDFS(m, 0);
    cout << "maze generated in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    m.addRandomLoops(5000);
    m.setWeight();

    t.reset();
    DFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    BFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    DijkstraSolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    AStarSolve(m, start, finish);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    cout << "finished solving" << endl;

    return 0;
  }

  else if (argc != 1 && *argv[1] == 'd') { // solve DFS+BFS+Dijkstra+A* no loops

    delayInBetween = 5000;
    delayGen = 0;
    delaySolve = 0;

    Maze m(180, 100); // width and height
    start = 9090;
    finish = 90;
    m.initGrid(start, finish);

    thread drawMaze(draw, ref(m));

    Timer t;
    RandomDFS(m, 0);
    cout << "maze generated in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    m.setWeight();

    t.reset();
    DFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    BFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    DijkstraSolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    AStarSolve(m, start, finish);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    cout << "finished solving" << endl;

    drawMaze.join();

    return 0;
  }

  else if (argc != 1 &&
           *argv[1] == 'e') { // solve DFS+BFS+Dijkstra+A* just time no loops

    delayInBetween = 0;
    delayGen = 0;
    delaySolve = 0;

    Maze m(180, 100); // width and height
    start = 9090;
    finish = 90;
    m.initGrid(start, finish);

    Timer t;
    RandomDFS(m, 0);
    cout << "maze generated in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    m.setWeight();

    t.reset();
    DFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    BFSsolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    DijkstraSolve(m, start);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    t.reset();
    AStarSolve(m, start, finish);
    cout << "maze solved in " << t.elapsed() << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(delayInBetween));

    cout << "finished solving" << endl;

    return 0;
  }

  return 0;
}
