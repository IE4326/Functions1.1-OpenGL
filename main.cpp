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
float Function(float x);

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

// Выдаёт ныне действующую формулу по значению переменно preset
// P.S. Я знаю что она ужасна
float Function(float x){
	float y;
	switch (preset){
		case 0:  y = x; break;
		case 1:  y = x*x; break;
		case 2:  y = x*x*x; break;
		case 3:  y = 1/(x*x); break;
		case 4:  y = 1/(x*x*x); break;
		case 5:  y = (x*x*x)-x; break;
		case 6:  y = 1/x; break;
		case 7:  y = (x*x*x)-6*(x*x)+11*x-4; break;
		case 8:  y = sqrt(x); break;
		case 9:  y = x * sqrt(x); break;
		case 10: y = sin(x); break;
		case 11: y = cos(x); break;
		case 12: y = tan(x); break;
		case 13: y = sin(x)*cos(x); break;
		case 14: y = asin(x); break;
		case 15: y = acos(x); break;
		case 16: y = atan(x); break;
		case 17: y = sqrt((sin(x)*sin(x))*(cos(x)*(cos(x))))*M_PI; break;
		default: break;
	}
	return y;
}

