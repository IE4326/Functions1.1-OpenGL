#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "vars.h"
#include "render.h"
#include "io.h"


int main(void)
{
   
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(WindowSize, WindowSize, "FUNCTIONS", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetMouseButtonCallback(window, MouseButton);
    glfwSetScrollCallback(window, Zoom);
    glfwSetCursorPosCallback(window, MouseMove);
    glfwSetKeyCallback(window, Keyboard);


    // Главный цикл находится здесь
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);
        DrawAxis();
        DrawGrid();
        if (FLAGS[FUNCTION]) DrawFunction();
        if (FLAGS[POINT]) DrawPoint();
        if (FLAGS[NAVIGATION]) DrawNavigation();
        if (FLAGS[TRIANGLE]) DrawTriangle();
        if (FLAGS[CENTER]) DrawCenter();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}