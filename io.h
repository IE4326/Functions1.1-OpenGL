#pragma once

#include "flags.h"

extern int WindowSize, PRESET;
extern double xAxisPos, yAxisPos, GridSize, PRECISION;
extern bool FLAGS[];
extern double xPoint, yPoint;

void MouseButton(GLFWwindow* window, int button, int action, int mods);
void Zoom(GLFWwindow* window, double xOffset, double yOffset);
void MouseMove(GLFWwindow* window, double x,  double y);
void Zoom(int scroll);
void PointInfo(int x, int y);
void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void ShowHelp();
void SetPreset(int i);
void SwitchPrecision();
double Function(double x);