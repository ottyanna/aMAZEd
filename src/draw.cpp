#include "draw.h"

int draw(Maze &maze) {

  maze.print();

  int lineWidth = 12;
  float gridSizeC = maze.columns;
  float gridSizeR = maze.rows;

  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(500, 500 * maze.rows / maze.columns, "Maze Solver",
                            NULL, NULL);
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

    int maxPathIndex = 0;

    for (int y = 0; y < maze.rows; y++) {
      for (int x = 0; x < maze.columns; x++) {

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
          glColor3f(1, 1, 1);
        }
        */

        glBegin(GL_QUADS);

        glVertex2f(-1 + (2 * x) / gridSizeC, 1 - (2 * y) / gridSizeR);
        glVertex2f(-1 + (2 * x) / gridSizeC + 2 / gridSizeC,
                   1 - (2 * y) / gridSizeR);
        glVertex2f(-1 + (2 * x) / gridSizeC + 2 / gridSizeC,
                   1 - ((2 * y) / gridSizeR) - 2 / gridSizeR);
        glVertex2f(-1 + (2 * x) / gridSizeC,
                   1 - ((2 * y) / gridSizeR) - 2 / gridSizeR);

        glEnd();

        glColor3f(0.3, 0, 0);

        /*
            // vertical walls
            if (walls[i + j * size][0] == 0) {
              for (int l = 1; l < lineWidth; l++) {
                glBegin(GL_LINES);
                glVertex2f(-1 + (2 * i) / gridSize + 0.001 * l,
                           1 - (2 * j) / gridSize);
                glVertex2f(-1 + (2 * i) / gridSize + 0.001 * l,
                           1 - ((2 * j) / gridSize) - 2 / gridSize);
                glEnd();
              }
            }

            // horizontal walls
            if (walls[i + j * size][1] == 0) {
              for (int l = 1; l < lineWidth; l++) {
                glBegin(GL_LINES);
                glVertex2f(-1 + (2 * i) / gridSize,
                           1 - (2 * j) / gridSize + 0.001 * l);
                glVertex2f(-1 + (2 * i) / gridSize + 2 / gridSize,
                           1 - (2 * j) / gridSize + 0.001 * l);
                glEnd();
              }
            }*/

        /*
        for (auto u : maze.adjMatrix) {
          if (x + y * maze.columns == u.node) {
            cout << u.node;
            cout << "heloo " << endl;
            if (u.edgeType == WALL) {
              if (u.adj == u.node + maze.columns) {
                for (int l = 1; l < lineWidth; l++) {
                  glBegin(GL_LINES);
                  glVertex2f(-1 + (2 * x) / gridSizeC,
                             1 - (2 * y) / gridSizeR + 0.001 * l);
                  glVertex2f(-1 + (2 * x) / gridSizeC + 2 / gridSizeC,
                             1 - (2 * y) / gridSizeR + 0.001 * l);
                  glEnd();
                }
              } else {
                for (int l = 1; l < lineWidth; l++) {
                  glBegin(GL_LINES);
                  glVertex2f(-1 + (2 * x) / gridSizeC + 0.001 * l,
                             1 - (2 * y) / gridSizeR);
                  glVertex2f(-1 + (2 * x) / gridSizeC + 0.001 * l,
                             1 - ((2 * y) / gridSizeR) - 2 / gridSizeR);
                  glEnd();
                }
              }
            }
          }
        }*/
      }
    }

    /*
        for (auto u : maze.adjMatrix) {
          cout << "pizza pazza" << endl;
          if (u.edgeType == WALL) {
            if (u.adj == u.node + maze.columns) {
              for (int l = 1; l < lineWidth; l++) {
                glBegin(GL_LINES);
                glVertex2f(-1 + (2 * x) / gridSizeR,
                           1 - (2 * y) / gridSizeC + 0.001 * l);
                glVertex2f(-1 + (2 * i) / gridSizeR + 2 / gridSizeR,
                           1 - (2 * j) / gridSizeC + 0.001 * l);
                glEnd();
              }
            } else {
              for (int l = 1; l < lineWidth; l++) {
                glBegin(GL_LINES);
                glVertex2f(-1 + (2 * i) / gridSizeR + 0.001 * l,
                           1 - (2 * j) / gridSizeC);
                glVertex2f(-1 + (2 * i) / gridSizeR + 0.001 * l,
                           1 - ((2 * j) / gridSizeC) - 2 / gridSizeC);
                glEnd();
              }
            }
          }
        }
        */

    // glScalef(zoomLevel, zoomLevel, 0.9f);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
