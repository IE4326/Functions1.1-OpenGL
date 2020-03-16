#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "io.h"

extern char NumberElements[];
extern double PRECISION;
extern double xPoint, yPoint;

void DrawAxis();
void DrawGrid();
void DrawPoint();
void DrawTriangle();
void DrawCenter();
void DrawNavigation();
void DrawFunction();
void DrawDigit(double x, double y, double size, int n);
void DrawArrow(double x, double y, double size, double angle);
void DrawNumber(double x, double y, double size, int n);