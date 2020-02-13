/*
	В этом файле будут содержатся функции необходиые для рисования
	разных отдельных графических элементов, типа стрелочек и цифр.
*/

char numbers[10] = {119, 36, 93, 109, 46, 107, 123, 39, 127, 111}; // В этом массиве будут хранится битвые маски, необходимые для отображения цифр.

/* Отображает одну цифру произвольного размера, в любом месте экрана.
получает в качестве аргументов верхнюю левую точку,
размер и саму цифру, которую нужно отобразить */
void DrawDigit(float x, float y, float size, int n){
	float m = 0.01*size;
	// Я не придумал ничего лучше чем хранить все необходимые точки в массивах
	float xpoint[7] = {x, x, x+m, x, x, x+m, x},
	      sxpoint[7] = {x+m, x, x+m, x+m, x, x+m, x+m},
	      ypoint[7] = {y, y, y, y-m, y-m, y-m, y-m-m},
	      sypoint[7] = {y, y-m, y-m, y-m, y-m-m, y-m-m, y-m-m};

	glLineWidth(2);
	for (int i = 0; i < 7; i++){
		if (numbers[n] >> i & 1){
			glBegin(GL_LINES);
				glVertex2f(xpoint[i], ypoint[i]);
				glVertex2f(sxpoint[i], sypoint[i]);
			glEnd();
		}
	}
	return;
}

// Рисует стрелку произвольного размера,
// указывающую на точку x y под углом angle
void DrawArrow(float x, float y, float size, float angle){
	float len = 0.03 * size,
	      width = len / 4,
	      pcx, pcy;
	angle = fmod(angle, M_PI*2);
	pcx = x + len * sin(angle);
	pcy = y + len * cos(angle);
	float px1, px2, py1, py2;
	angle = fmod(angle+M_PI/2, M_PI*2);
	px1 = pcx + width * sin(angle);
	py1 = pcy + width * cos(angle);
	px2 = pcx - width * sin(angle);
	py2 = pcy - width * cos(angle);
	glBegin(GL_LINE_STRIP);
		glVertex2f(px1, py1);
		glVertex2f(x, y);
		glVertex2f(px2, py2);
	glEnd();
	return;
}

// Последовательно вызывает рисование отдельных цифр чтобы отобразить нужное число
void DrawNumber(float x, float y, float size, int n){
	int razr = 0;
	for (int i = n; i>0 || !razr; i/=10) razr++;
	int a;
	for (int m = 0;razr>0;razr--,m++, n%=10){
		a = 1;
		for (int i = razr; i > 0; i--){
			a*=10;
		}
		a/=10;
		DrawDigit(x+size*m*0.02, y, size, n/a);
	}
}
