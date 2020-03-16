#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <GLFW/glfw3.h>
#include <iostream>

#include "io.h"

void MouseButton(GLFWwindow* window, int Button, int State, int mods)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (Button == GLFW_MOUSE_BUTTON_LEFT && State == GLFW_PRESS)
	{
		FLAGS[MOVING] = true;
		return;
	}

	if (Button == GLFW_MOUSE_BUTTON_LEFT && State == GLFW_RELEASE)
	{
		FLAGS[MOVING] = false;
		return;
	}

	if (Button == GLFW_MOUSE_BUTTON_RIGHT && State == GLFW_PRESS)
	{
		PointInfo(x, y);
	}

}

void Zoom(GLFWwindow* window, double xOffset, double yOffset)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	// Чтобы осуществить зум, сначала запоминаем в какой клетке находится курсор
	double xCell, yCell;
	double HalfWindowSize = WindowSize / 2;
	xCell = (double)(x - HalfWindowSize) / HalfWindowSize;
	yCell = (double)(y - HalfWindowSize) / HalfWindowSize;

	// Отсчитываем количество клеток до курсора от начала координат
	double xCellCount, yCellCount;
	xCellCount = (xCell - yAxisPos) / GridSize;
	yCellCount = (-yCell - xAxisPos) / GridSize;

	// Увеличиваем/уменьшаем размер сетки и подгоняем положение осей по запомненому состоянию
	if (yOffset > 0 && GridSize < 40) 
		GridSize *= 1.5; else
	if (yOffset < 0 && GridSize > 0.01) 
		GridSize /= 1.5;
	xAxisPos = -yCell - (yCellCount * GridSize);
	yAxisPos = xCell - (xCellCount* GridSize);

	FLAGS[POINT] = false;
}

void MouseMove(GLFWwindow* window, double x, double y)
{
	// Для плавного премещения храним значение последнего положения курсора
	static double xLast, yLast;

	if (FLAGS[MOVING])
	{
		// 2.0 - размер всего экрана. Соответственно, высчитываем количество клеток, которые помещаются на экран
		double CellCount = 2.0 / GridSize;
		double CellSize = WindowSize / CellCount;
		yAxisPos += GridSize * ( (x - xLast) / CellSize);
		xAxisPos += GridSize * ( (yLast - y) / CellSize);
		FLAGS[POINT] = false;
	}

	xLast = x, yLast = y;
}

void PointInfo(int x, int y)
{
	double xFloat = (double)x / (WindowSize / 2) - 1; // Чтобы вывести информацию о заданной точке сначала получаем её положение на экране от -1.0 до 1.0
	double Cell = -(yAxisPos - xFloat) / GridSize;
	FLAGS[POINT] = true;
	xPoint = yAxisPos + Cell * GridSize;
	yPoint = xAxisPos + (Function(Cell)) * GridSize;
	std::cout << "FOR x = " << Cell << ", Y = " << Function(Cell) << std::endl;
}

void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
	{
		return;
	}

	if (key >= 48 && key <= 57)
	{
		SetPreset(key - 48);
		return;
	}

	if (key == 84)
	{
		FLAGS[TRIANGLE] ^= 1;
		return;
	}

	if (key == 67)
	{
		FLAGS[CENTER] ^= 1;
		return;
	}

	if (key == 78)
	{
		FLAGS[NAVIGATION] ^= 1;
		return;
	}

	if (key == 70)
	{
		FLAGS[FUNCTION] ^= 1;
		return;
	}

	if (key == 83)
	{
		SetPreset(key);
		return;
	}

	if (key == 72)
	{
		ShowHelp();
		return;
	}

	if (key == 80)
	{
		SwitchPrecision();
		return;
	}
}

void SetPreset(int i)
{
	static bool SequenceFlag = false; // Если ожидается вторая цифра, или команда переключения
	static int First;
	if (SequenceFlag) {
		SequenceFlag = false;
		int Preset = i == 83 ? First : (First * 10) + i;
		if (Preset > 17 || Preset < 0) return;
		PRESET = Preset;
		std::cout << "PRESET IS NOW" << Preset << "!\n";
		return;
	}
	else {
		First = i;
		SequenceFlag = true;
		return;
	}
}

void SwitchPrecision()
{
	PRECISION = PRECISION / 2 >= 0.0125 ? PRECISION / 2 : 0.2;
	std::cout << "PRECISION IS NOW " << PRECISION << "!\n";
}

void ShowHelp()
{
	std::cout << "HELP:\n____\n" <<
		"KEYS: t - toggle triangle, c - toggle center point, n - toggle navigationarrow\n" <<
		"0-9 - to switch preset, s - set preset (with one number), h - help\n" <<
		"p - switch precision level\n" <<
		"\nPRESET NUMBERS:\n" <<
		"0. y = x;\n" <<
		"1. y = x^2;\n" <<
		"2. y = x^3;\n" <<
		"3. y = 1/(x^2);\n" <<
		"4. y = 1/(x^3);\n" <<
		"5. y = x^3-x;\n" <<
		"6. y = 1/x;\n" <<
		"7. y = x^3-6x^2+11x-4;\n" <<
		"8. y = sqrt(x);\n" <<
		"9. y = x * sqrt(x);\n" <<
		"10. y = sin(x);\n" <<
		"11. y = cos(x);\n" <<
		"12. y = tan(x);\n" <<
		"13. y = sin(x)*cos(x);\n" <<
		"14. y = asin(x);\n" <<
		"15. y = acos(x);\n" <<
		"16. y = atan(x);\n" <<
		"17. y = sqrt(sin(x)^2 * cos(x)^2) * Pi;\n";
}

double Function(double x) {
	double y;
	switch (PRESET) {
	case 0:  y = x; break;
	case 1:  y = x * x; break;
	case 2:  y = x * x * x; break;
	case 3:  y = 1 / (x * x); break;
	case 4:  y = 1 / (x * x * x); break;
	case 5:  y = (x * x * x) - x; break;
	case 6:  y = 1 / x; break;
	case 7:  y = (x * x * x) - 6 * (x * x) + 11 * x - 4; break;
	case 8:  y = sqrt(x); break;
	case 9:  y = x * sqrt(x); break;
	case 10: y = sin(x); break;
	case 11: y = cos(x); break;
	case 12: y = tan(x); break;
	case 13: y = sin(x) * cos(x); break;
	case 14: y = asin(x); break;
	case 15: y = acos(x); break;
	case 16: y = atan(x); break;
	case 17: y = sqrt((sin(x) * sin(x)) * (cos(x) * (cos(x)))) * M_PI; break;
	default: break;
	}
	return y;
}
