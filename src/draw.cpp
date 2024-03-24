#include "draw.h"

float zoomLevel = 1.0;

const float indigo[] = {0.294, 0.000, 0.510};
const float plum[] = {0.867, 0.627, 0.867};
const float gold[] = {1.000, 0.843, 0.000};
const float cyan[] = {0.000, 1.000, 1.000}; // finish
const float greenYellow[] = {0.678, 1.000, 0.184};
const float black[] = {0, 0, 0};
const float deepPink[] = {1.000, 0.078, 0.576};
const float darkOrange[] = {1.000, 0.549, 0.000};
const float limeGreen[] = {0.196, 0.804, 0.196}; // start

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

  int lineWidth = 0;

  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  const float ratio = static_cast<float>(maze.nColumns) / maze.nRows;

  int wHeight = 700;
  int wWidth = static_cast<int>(wHeight * ratio);

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
  float scaleY = -2. / (yMax - yMin);

  float translateX = -1. - xMin * scaleX;
  float translateY = +1. - yMin * scaleY;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    // int maxPathIndex = 0;

    for (int y = 0; y < maze.nRows; y++) {
      for (int x = 0; x < maze.nColumns; x++) {

        int pNode = x + y * maze.nColumns;

        if (maze.vertices[pNode].type == START)
          glColor3fv(limeGreen);
        else if (maze.vertices[pNode].type == FINISH)
          glColor3fv(cyan);
        else if (maze.vertices[pNode].type == PATH)
          glColor3fv(deepPink);
        else if (maze.vertices[pNode].color == GREY)
          glColor3fv(gold);
        else if (maze.vertices[pNode].color == BLACK)
          glColor3fv(indigo);
        else
          glColor3fv(plum);

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
        // glPointSize(5);
        //
        // glBegin(GL_POINTS);
        //
        // glColor3f(0.3, 0.3, 0);
        // glVertex2f(scaleX * x + translateX, scaleY * y + translateY);
        //
        // glEnd();
        //

        // walls size
        glLineWidth(lineWidth);
        // walls color
        glColor3fv(black);

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
