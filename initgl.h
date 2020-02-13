/*Не на что тут смотреть */
void InitializeGlut();
void Reshape(int Width, int Height);

void InitializeGlut(){
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(WindowSize, WindowSize);
	glutCreateWindow("FUNCTIONS");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glClearColor(0.1,0.1,0.1,0.0);
}

void Reshape(int Width, int Height){
	glViewport(0, 0, WindowSize, WindowSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
