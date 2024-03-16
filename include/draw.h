#ifndef DRAW_H
#define DRAW_H

#include "maze.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <map>
#include <string>
#include <thread>

using namespace std;

int draw(Maze &, GLFWwindow *);

#endif