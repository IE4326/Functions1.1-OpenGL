void Mouse(int Button, int State, int x, int y);
void Move(int x, int y);
void Scale(int x, int y, bool mag);
void Motion(int x, int y);
void PointInfo(int x, int y);

void Mouse(int Button, int State, int x, int y){
	if (Button == 0 && State == 0){
		xvpoint = x;
		yvpoint = y;
		moving = true;
		return;
	}
	if (Button == 0 && State == 1){
		moving = false;
		return;
	}
	if ((Button == 3 || Button == 4) && State == 1){
		Scale(x, y, (Button == 3));
	}
	if (Button == 2 && State == 1){
		PointInfo(x, y);
	}
	Display();
}

// xvpoint и yvpoint хранят положение курсора во время последнего движения
// Используются для реализации плавного перемещения
void Motion(int x, int y){
	if (!moving) return;
	Move(-(xvpoint-x), (yvpoint-y));
	xvpoint = x;
	yvpoint = y;
}

void Move(int x, int y){
	float cellcount = 2.0 / GridSize;
	float cellsize = WindowSize / cellcount;
	yLinePos += GridSize*(x/cellsize);
	xLinePos += GridSize*(y/cellsize);
	point = false;
	Display();
	return;
}

// Увеличивает или уменьшает размер сетки. В зависимости от флага mag
void Scale(int x, int y, bool mag){
	float xc, yc;
	float half = WindowSize/2;
	xc = (float)(x-half)/half;
	yc = (float)(y-half)/half;
	float xcells, ycells;
	xcells = (xc-yLinePos) / GridSize;
	ycells = (-yc-xLinePos) / GridSize;
	if (mag && GridSize < 40) GridSize*=1.5; else 
	if (!mag && GridSize > 0.01) GridSize/=1.5;
	xLinePos = -yc - (ycells*GridSize);
	yLinePos = xc - (xcells*GridSize);
	point = false;
	return;
}

// Выводит в консоль информацию о точке (нажатие ПКМ)
void PointInfo(int x, int y){
	float xf = (float)x/(WindowSize/2)-1;
	float cel = -(yLinePos-xf)/GridSize;
	point = true;
	pointx = yLinePos+cel*GridSize;
	pointy = xLinePos+(Function(cel))*GridSize;
	std::cout << "FOR x = " << cel << ", Y = " << Function(cel) << std::endl;
	return;
}

