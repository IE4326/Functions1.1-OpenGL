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
