#include "draw.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

float zoomLevel = 1.0;

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
  if (yOffset > 0) {
    zoomLevel += 0.01;
  } else {
    zoomLevel -= 0.01;
  }

  if (zoomLevel < 0.5)
    zoomLevel = 0.5;
}

int draw(Maze &maze) {

  int lineWidth = 12;

  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  const float ratio = static_cast<float>(maze.nColumns) / maze.nRows;

  int wWidth = 600;
  int wHeight = static_cast<int>(wWidth / ratio);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(wWidth, wHeight, "Maze Solver ", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // Set scroll callback function
  glfwSetScrollCallback(window, scrollCallback);

  float xMin = -0.5;
  float xMax = maze.nColumns + 0.5;
  float yMin = -0.5;
  float yMax = maze.nRows + 0.5;

  float scaleX = 2. / (xMax - xMin);
  float scaleY = 2. / (yMax - yMin);

  float translateX = -1. - xMin * scaleX;
  float translateY = -1. - yMin * scaleY;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    // int maxPathIndex = 0;

    for (int y = 0; y < maze.nRows; y++) {
      for (int x = 0; x < maze.nColumns; x++) {

        // j is y
        // i is x

        // int position = i + j * size;
        // int cpathIndex = path[i + size * j];

        /*if (cpathIndex > maxPathIndex) {
          maxPathIndex = cpathIndex;
        }
        if (position == pos) {
          glColor3f(0, 1, 0);
        } else if (position == start) {
          glColor3f(1, 0, 0);
        } else if (cpathIndex == -1) {
          glColor3f(1, 1, 0.4);
        } else if (mazeBlocks[position][3] != 0) {
          glColor3f(0.7, 1, 0.7);
        } else if (mazeBlocks[position][2] != 0) {
          glColor3f(0.6, 0.6, 1);
        } else if (cpathIndex > 0) {
          glColor3f(1, 0.6, 0.6);
        } else {

          glColor3f(1, 1, 1); //background color
        }
        */

        glColor3f(0.3, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(scaleX * (x - 0.5) + translateX,
                   scaleY * (y + 0.5) + translateY);
        glVertex2f(scaleX * (x + 0.5) + translateX,
                   scaleY * (y + 0.5) + translateY);
        glVertex2f(scaleX * (x + 0.5) + translateX,
                   scaleY * (y - 0.5) + translateY);
        glVertex2f(scaleX * (x - 0.5) + translateX,
                   scaleY * (y - 0.5) + translateY);
        glEnd();

        // set size to 1 for a group of points
        glPointSize(5);

        glBegin(GL_POINTS);

        glColor3f(0.3, 0.3, 0);
        glVertex2f(scaleX * x + translateX, scaleY * y + translateY);

        glEnd();

        int pNode = x + y * maze.nColumns;

        glLineWidth(lineWidth);
        // walls color
        glColor3f(0, 0, 0);

        for (auto u : maze.adjList[pNode]) {
          if (u.edgeType == WALL) {
            if (u.adjPtr->id ==
                pNode + maze.nColumns) { // adiacente sotto // horizontal walls

              glBegin(GL_LINES);

              glVertex2f(scaleX * (x - 0.5) + translateX,
                         scaleY * (y + 0.5) + translateY);
              glVertex2f(scaleX * (x + 0.5) + translateX,
                         scaleY * (y + 0.5) + translateY);
              glEnd();

            } else if (u.adjPtr->id ==
                       pNode - maze.nColumns) { // adiacente sopra //horizontal
                                                // walls

              glBegin(GL_LINES);

              glVertex2f(scaleX * (x - 0.5) + translateX,
                         scaleY * (y - 0.5) + translateY);
              glVertex2f(scaleX * (x + 0.5) + translateX,
                         scaleY * (y - 0.5) + translateY);

              glEnd();

            } else if (u.adjPtr->id == pNode - 1) { // a sx // vertical walls

              glBegin(GL_LINES);

              glVertex2f(scaleX * (x - 0.5) + translateX,
                         scaleY * (y + 0.5) + translateY);
              glVertex2f(scaleX * (x - 0.5) + translateX,
                         scaleY * (y - 0.5) + translateY);

              glEnd();
            } else if (u.adjPtr->id == pNode + 1) { // a sx // vertical walls

              glBegin(GL_LINES);

              glVertex2f(scaleX * (x + 0.5) + translateX,
                         scaleY * (y - 0.5) + translateY);
              glVertex2f(scaleX * (x + 0.5) + translateX,
                         scaleY * (y + 0.5) + translateY);

              glEnd();
            }
          }
        }
      }
    }

    glScalef(zoomLevel, zoomLevel, 0.1);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
