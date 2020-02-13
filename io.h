/*
	Управление с клавиатуры и вывод справки в консоль
   */

void Keyboard(unsigned char key, int x, int y);
void ShowHelp();
void SetPreset(int i);
void SwitchPrecision();

void Keyboard(unsigned char key, int x, int y){
	switch (key){
		case 't': triangle^=1; Display(); return;
		case 'c': center^=1; Display(); return;
		case 'n': navigation^=1; Display(); return;
		case 'f': function^=1; Display(); return;
		case 's': SetPreset(key-48); return;
		case 'h': ShowHelp(); return;
		case 'p': SwitchPrecision(); break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		default: break;
	}
}

void ShowHelp(){
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

// Хранит первое нажатие цифры. При втором нажатии меняет режим 
void SetPreset(int i){
	static bool sequence = false;
	static int first;
	if (sequence){
		sequence = false;
		int pr = i == 67 ? first : (first*10)+i;
		if (pr > 17 || pr < 0) return;
		preset = pr;
		std::cout << "PRESET IS " << pr << "!\n";
		Display();
		return;
	} else {
		first = i;
		sequence = true;
		return;
	}
}

void SwitchPrecision(){
	precision = precision / 2 >= 0.0125 ? precision / 2 : 0.2;
	std::cout << "PRECISION IS NOW " << precision << "!\n";
	Display();
	return;
}
