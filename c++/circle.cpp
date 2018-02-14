#include <GL/glut.h>					// (or others, depending on the system in use)
#include <bevgrafmath2017.h>
#include <math.h>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;
GLdouble k = 0;
GLdouble jobbbal = 200.0,lefel = 300.0;
GLdouble delta = 0.1;
GLint keyStates[256];

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void circle(vec2 O, GLdouble r) {
	
	glBegin(GL_LINE_STRIP);
	for (GLdouble t = k; t <=  (pi()/2)+k; t += 0.01)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations() {
	if (keyStates['a']) { jobbbal -= delta; }
	if (keyStates['d']) { jobbbal += delta; }

	if (keyStates['s']) { lefel -= delta; }
	if (keyStates['w']) { lefel += delta; }


	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'j':
		jobbbal -= delta;
		break;
	case 'l':
		jobbbal += delta;
		break;
	case 'k':
		lefel -= delta;
		break;
	case 'i':
		lefel += delta;
		break;
	}
}


void draw()
{
	keyOperations();
	
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);
	
	circle(vec2(jobbbal, lefel), 100);

	glutSwapBuffers();
}

void update(int n)
{
	//std::cout<<jobbbal<<std::endl;
	
	k+=0.01;

	glutPostRedisplay();

	glutTimerFunc(5, update, 0);

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(400, 300);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	glutDisplayFunc(draw);       // Send graphics to display window.
	glutTimerFunc(5, update, 0);
	glutKeyboardFunc(keyPressed);
	//glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();                    // Display everything and wait.
	return 0;
}