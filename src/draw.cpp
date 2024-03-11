#include "draw.h"
#include <GL/gl.h>

GLfloat pointX(int coo, int N) { return (2.0 * coo - N) / (N + 1.0); }
GLfloat pointY(int coo, int N) { return (-2.0 * coo - N) / (N + 1.0); }

int draw(Maze &maze) {

  int lineWidth = 12;
  float gridSizeC = maze.nColumns;
  float gridSizeR = maze.nRows;

  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  GLfloat ratio = maze.nColumns / maze.nRows;
  GLint wHeight = 500;
  GLint wWidth = wHeight * ratio;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(wWidth, wHeight, "Maze Solver ", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

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
        } else {/*

          glColor3f(1, 1, 1); //background color
        }
        */

        glBegin(GL_QUADS);

        glColor3f(0, 1, 0);

        glVertex2f(pointX(x + 0.5, gridSizeC), pointY(y + 0.5, gridSizeR));
        glVertex2f(pointX(x + 0.5, gridSizeC), pointY(y - 0.5, gridSizeR));
        glVertex2f(pointX(x - 0.5, gridSizeC), pointY(y + 0.5, gridSizeR));
        glVertex2f(pointX(x - 0.5, gridSizeC), pointY(y - 0.5, gridSizeR));

        glEnd();

        glBegin(GL_POINTS);
        glColor3f(1, 0, 0); // background color
        // set size to 1 for a group of points
        glPointSize(10);

        glVertex2f(pointX(x, gridSizeC), pointY(y, gridSizeR));
        // glVertex2f((2.0 * x) / gridSizeC - 1.0, 1.0 - (2.0 * y) / gridSizeR);
        glEnd();

        glColor3f(0, 0, 1); // line color

        int pNode = x + y * maze.nColumns;

        glLineWidth(1);

        for (auto u : maze.adjList[pNode]) {
          if (u.edgeType == WALL) {
            if (u.adjPtr->id ==
                pNode + maze.nColumns) { // adiacente sotto // horizontal walls

              glBegin(GL_LINES);

              glVertex2f((2.0 * (x - 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y + 0.5)) / gridSizeR);
              glVertex2f((2.0 * (x + 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y + 0.5)) / gridSizeR);
              glEnd();

            } else if (u.adjPtr->id ==
                       pNode - maze.nColumns) { // adiacente sopra // horizontal
                                                // walls

              glBegin(GL_LINES);

              glVertex2f((2.0 * (x - 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y - 0.5)) / gridSizeR);
              glVertex2f((2.0 * (x + 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y - 0.5)) / gridSizeR);
              glEnd();

            } else if (u.adjPtr->id == pNode - 1) { // a sx // vertical walls

              glBegin(GL_LINES);

              glVertex2f((2.0 * (x - 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y + 0.5)) / gridSizeR);
              glVertex2f((2.0 * (x - 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y - 0.5)) / gridSizeR);
              glEnd();
            } else if (u.adjPtr->id == pNode + 1) { // a sx // vertical walls

              glBegin(GL_LINES);

              glVertex2f((2.0 * (x + 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y - 0.5)) / gridSizeR);
              glVertex2f((2.0 * (x + 0.5)) / gridSizeC - 1,
                         (1 - 2.0 * (y + 0.5)) / gridSizeR);
              glEnd();
            }
          }
        }
      }
    }

    // glScalef(zoomLevel, zoomLevel, 0.9f);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
