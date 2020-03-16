#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "render.h"

extern double xAxisPos, yAxisPos, GridSize;

void DrawAxis()
{
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-1.0, xAxisPos);
	glVertex2f(1.0, xAxisPos);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(yAxisPos, -1.0);
	glVertex2f(yAxisPos, 1.0);
	glEnd();
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(yAxisPos, xAxisPos);
	glEnd();
	DrawArrow(1.0, xAxisPos, 1, M_PI / 2 + M_PI);
	DrawArrow(yAxisPos, 1.0, 1, M_PI);
}

void DrawGrid()
{
	int c = (2.0 + abs(xAxisPos) + abs(yAxisPos)) / GridSize; // Количество клеток, которые помещаются на экран
	double opacity = 0.15 + GridSize > 0.6 ? 0.6 : 0.15 + GridSize;
	for (int x = c; x > 0; x--) {
		glColor3f(opacity, opacity, opacity);
		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2f(yAxisPos + GridSize * x, -1.0);
		glVertex2f(yAxisPos + GridSize * x, 1.0);

		glVertex2f(yAxisPos - GridSize * x, -1.0);
		glVertex2f(yAxisPos - GridSize * x, 1.0);

		glVertex2f(-1.0, xAxisPos + GridSize * x);
		glVertex2f(1.0, xAxisPos + GridSize * x);

		glVertex2f(-1.0, xAxisPos - GridSize * x);
		glVertex2f(1.0, xAxisPos - GridSize * x);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(yAxisPos + GridSize * x, xAxisPos - GridSize / 12);
		glVertex2f(yAxisPos + GridSize * x, xAxisPos + GridSize / 12);

		glVertex2f(yAxisPos - GridSize * x, xAxisPos - GridSize / 12);
		glVertex2f(yAxisPos - GridSize * x, xAxisPos + GridSize / 12);

		glVertex2f(yAxisPos - GridSize / 12, xAxisPos + GridSize * x);
		glVertex2f(yAxisPos + GridSize / 12, xAxisPos + GridSize * x);

		glVertex2f(yAxisPos - GridSize / 12, xAxisPos - GridSize * x);
		glVertex2f(yAxisPos + GridSize / 12, xAxisPos - GridSize * x);
		glEnd();
		if (GridSize > 0.02) {
			DrawNumber(yAxisPos + GridSize * x, xAxisPos - 0.02, 4 * GridSize, x);
			DrawNumber(yAxisPos + 0.1 * GridSize, xAxisPos + GridSize * x, 4 * GridSize, x);
			DrawNumber(yAxisPos - GridSize * x, xAxisPos - 0.02, 4 * GridSize, x);
			DrawNumber(yAxisPos + 0.1 * GridSize, xAxisPos - GridSize * x, 4 * GridSize, x);
		}
	}
	DrawDigit(yAxisPos + 0.03, xAxisPos - 0.01, 4 * GridSize, 0);
}

void DrawPoint()
{
	glColor3f(0.7, 0.25, 0.25);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(xPoint, yPoint);
	glEnd();
}

void DrawTriangle()
{
	double vector = sqrt((yAxisPos * yAxisPos) + (xAxisPos * xAxisPos));
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.25, 0.7, 0.25);
	glVertex2f(yAxisPos, xAxisPos);
	glVertex2f(0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(yAxisPos, xAxisPos);
	glVertex2f(yAxisPos, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex2f(yAxisPos, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();
	glColor3f(0.25, 0.7, 0.25);
	DrawNumber(-0.95, 0.95, 2, vector / GridSize);
	glColor3f(1.0, 1.0, 0.0);
	DrawNumber(-0.95, 0.88, 2, abs(xAxisPos) / GridSize);
	glColor3f(1.0, 0.0, 1.0);
	DrawNumber(-0.95, 0.81, 2, abs(yAxisPos) / GridSize);
}

void DrawCenter()
{
	glColor3f(0.7, 0.25, 0.25);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2f(0.0, 0.0);
	glEnd();
}

void DrawNavigation()
{
	if (!(yAxisPos < -1.0 || yAxisPos > 1.0 || xAxisPos < -1.0 || xAxisPos > 1.0)) return;
	double radius = 0.99;
	double angle = atan2(yAxisPos, xAxisPos) + M_PI;
	double vector = sqrt((yAxisPos * yAxisPos) + (xAxisPos * xAxisPos));
	double x = -sin(angle), y = -cos(angle);
	double margin = yAxisPos > 0 ? -0.14 : +0.04;
	glColor3f(1.0, 1.0, 1.0);
	DrawArrow(x * radius, y * radius, 2, angle);
	DrawNumber(x * (radius - 0.07) + margin, y * (radius - 0.07), 2, vector / GridSize);
}

void DrawFunction()
{
	int c = (2.0 + abs(xAxisPos) + abs(yAxisPos)) / GridSize;
	glColor3f(0.7, 0.25, 0.25);
	double backtrack = 0;
	glBegin(GL_LINE_STRIP);
	for (double x = -c; x < c; x += PRECISION) {
		if (abs(backtrack - (Function(x))) > 300) {
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		glVertex2f(yAxisPos + x * GridSize, xAxisPos + (Function(x)) * GridSize);
		backtrack = Function(x);
	}
	glEnd();
}

void DrawDigit(double x, double y, double size, int n)
{
	double m = 0.01 * size;
	// Массивы, которые хранят положение элементов по принципу электронного циферблата
	double xpoint[7] = { x, x, x + m, x, x, x + m, x },
		sxpoint[7] = { x + m, x, x + m, x + m, x, x + m, x + m },
		ypoint[7] = { y, y, y, y - m, y - m, y - m, y - m - m },
		sypoint[7] = { y, y - m, y - m, y - m, y - m - m, y - m - m, y - m - m };

	glLineWidth(2);
	for (int i = 0; i < 7; i++) {
		if (NumberElements[n] >> i & 1) {
			glBegin(GL_LINES);
			glVertex2f(xpoint[i], ypoint[i]);
			glVertex2f(sxpoint[i], sypoint[i]);
			glEnd();
		}
	}
}

// Рисует стрелку в произвольном месте, заданного размера, под заданным углом
void DrawArrow(double x, double y, double size, double angle)
{
	double len = 0.03 * size,
		width = len / 4,
		pcx, pcy;
	angle = fmod(angle, M_PI * 2);
	pcx = x + len * sin(angle);
	pcy = y + len * cos(angle);
	double px1, px2, py1, py2;
	angle = fmod(angle + M_PI / 2, M_PI * 2);
	px1 = pcx + width * sin(angle);
	py1 = pcy + width * cos(angle);
	px2 = pcx - width * sin(angle);
	py2 = pcy - width * cos(angle);
	glBegin(GL_LINE_STRIP);
	glVertex2f(px1, py1);
	glVertex2f(x, y);
	glVertex2f(px2, py2);
	glEnd();
}

// Последовательно вызывает DrawDigit() для вывода числа
void DrawNumber(double x, double y, double size, int n)
{
	int razr = 0;
	for (int i = n; i > 0 || !razr; i /= 10) razr++;

	while (razr > 0)
	{
		DrawDigit(x + razr*0.02*size, y, size, n%10);
		n /= 10;
		razr--;
	}
}
