#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "figures.h"

int WindowSize = 1000,
	preset = 0;

float xLinePos = 0.0, yLinePos = 0.0, // Положения осей X и Y на экране. По умолчанию в центре
	GridSize = 0.2, // Размер одной клетки
	xvpoint, yvpoint,
	pointx, pointy,
	precision = 0.1; // Чем ниже, тем больше точек на отрезке. Отражает качетво отображения

bool moving = false, // TRUE, когда производится движение мышью
     	// Флаги отображения разных элементов
	point = false, 
	triangle = false,
	center = false,
	navigation = true,
	function = true;

void Display();

#include "getfunction.h"
#include "io.h"
#include "render.h"
#include "mouse.h"
#include "initgl.h"

int main(int argc, char** argv){
	glutInit(&argc, argv);
	InitializeGlut(); // Все стандартные процедуры для GLUT
	glutMainLoop();
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	DrawAxis();
	DrawGrid();
	if (function) DrawFunction();
	if (point) DrawPoint();
	if (navigation) DrawNavigation();
	if (triangle) DrawTriangle();
	if (center) DrawCenter();
	glutSwapBuffers();
}



