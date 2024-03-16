#ifndef DRAW_H
#define DRAW_H

#include "maze.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

int draw(Maze &, GLFWwindow *);

#endif