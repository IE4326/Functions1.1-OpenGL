/* 
   Вся основная масса того что рисуется на экране
*/

void DrawFunction();
void DrawNavigation();
void DrawCenter();
void DrawTriangle();
void DrawPoint();
void DrawGrid();
void DrawAxis();

void DrawAxis(){
	glColor3f(1.0,1.0,1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex2f(-1.0, xLinePos);
		glVertex2f(1.0, xLinePos);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(yLinePos, -1.0);
		glVertex2f(yLinePos, 1.0);
	glEnd();
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex2f(yLinePos, xLinePos);
	glEnd();
	DrawArrow(1.0, xLinePos, 1, M_PI/2+M_PI);
	DrawArrow(yLinePos, 1.0, 1, M_PI);
}

void DrawGrid(){
	int c = (2.0+abs(xLinePos)+abs(yLinePos))/GridSize; // Количество клеток, которые помещаются на экран
	float opacity = 0.15+GridSize > 0.6 ? 0.6 : 0.15+GridSize;
	for (int x = c; x > 0; x--){
		glColor3f(opacity, opacity, opacity);
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex2f(yLinePos + GridSize*x, -1.0);
			glVertex2f(yLinePos + GridSize*x, 1.0);

			glVertex2f(yLinePos - GridSize*x, -1.0);
			glVertex2f(yLinePos - GridSize*x, 1.0);
			
			glVertex2f(-1.0, xLinePos + GridSize*x);
			glVertex2f(1.0, xLinePos + GridSize*x);

			glVertex2f(-1.0, xLinePos - GridSize*x);
			glVertex2f(1.0, xLinePos - GridSize*x);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex2f(yLinePos + GridSize*x, xLinePos-GridSize/12);
			glVertex2f(yLinePos + GridSize*x, xLinePos+GridSize/12);

			glVertex2f(yLinePos - GridSize*x, xLinePos-GridSize/12);
			glVertex2f(yLinePos - GridSize*x, xLinePos+GridSize/12);
			
			glVertex2f(yLinePos-GridSize/12, xLinePos + GridSize*x);
			glVertex2f(yLinePos+GridSize/12, xLinePos + GridSize*x);

			glVertex2f(yLinePos-GridSize/12, xLinePos - GridSize*x);
			glVertex2f(yLinePos+GridSize/12, xLinePos - GridSize*x);
		glEnd();
		if (GridSize > 0.02){
			DrawNumber(yLinePos + GridSize*x, xLinePos - 0.02, 4*GridSize, x);
			DrawNumber(yLinePos + 0.03, xLinePos+GridSize*x, 4*GridSize, x);
			DrawNumber(yLinePos - GridSize*x, xLinePos - 0.02, 4*GridSize, x);
			DrawNumber(yLinePos - 0.05, xLinePos-GridSize*x, 4*GridSize, x);
		}
	}
			DrawDigit(yLinePos + 0.03, xLinePos - 0.01, 4*GridSize, 0);
}

void DrawPoint(){
	glColor3f(0.7,0.25,0.25);
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2f(pointx, pointy);
	glEnd();
}

void DrawTriangle(){
	float vector = sqrt((yLinePos * yLinePos) + (xLinePos * xLinePos));
	glLineWidth(1);
	glBegin(GL_LINES);
		glColor3f(0.25,0.7,0.25);
		glVertex2f(yLinePos, xLinePos);
		glVertex2f(0.0, 0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(yLinePos,xLinePos);
		glVertex2f(yLinePos, 0.0);
		glColor3f(1.0,0.0,1.0);
		glVertex2f(yLinePos, 0.0);
		glVertex2f(0.0,0.0);
	glEnd();
	glColor3f(0.25,0.7,0.25);
	DrawNumber(-0.95,0.95, 2, vector/GridSize);
	glColor3f(1.0,1.0,0.0);
	DrawNumber(-0.95,0.88, 2, abs(xLinePos)/GridSize);
	glColor3f(1.0,0.0,1.0);
	DrawNumber(-0.95,0.81, 2, abs(yLinePos)/GridSize);
}

void DrawCenter(){
	glColor3f(0.7,0.25,0.25);
	glPointSize(4);
	glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	glEnd();
	return;
}

void DrawNavigation(){
	if (!(yLinePos < -1.0 || yLinePos > 1.0 || xLinePos < -1.0 || xLinePos > 1.0)) return;
	float radius = 0.99;
	float angle = atan2(yLinePos , xLinePos)+M_PI;
	float vector = sqrt((yLinePos * yLinePos) + (xLinePos * xLinePos));
	float x = -sin(angle), y = -cos(angle);
	float margin = yLinePos>0 ? -0.14 : +0.04;
	glColor3f(1.0, 1.0, 1.0);
	DrawArrow(x*radius,y*radius,2,angle);
	DrawNumber(x*(radius-0.07)+margin,y*(radius-0.07),2,vector/GridSize);
}

void DrawFunction(){
	int c = (2.0+abs(xLinePos)+abs(yLinePos))/GridSize;
	glColor3f(0.7,0.25,0.25);
	float backtrack;
	glBegin(GL_LINE_STRIP);
	for (float x = -c; x < c; x += precision){
		if ( abs(backtrack - (Function(x))) > 300 ){
			glEnd();
			glBegin(GL_LINE_STRIP);
		}
		glVertex2f(yLinePos+x*GridSize, xLinePos+(Function(x))*GridSize);
		backtrack = Function(x);
	}
	glEnd();
}

