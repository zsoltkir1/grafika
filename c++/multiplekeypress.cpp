#include <GL/glut.h>
#include <bevgrafmath2017.h>

GLint keyStates[256];

vec2 pointA = { 100, 40 };
vec2 pointB = { 200, 200 };

GLfloat delta = 0.01;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void keyOperations() {
	if (keyStates['a']) { pointA.x -= delta; }
	if (keyStates['d']) { pointA.x += delta; }

	if (keyStates['s']) { pointB.y -= delta; }
	if (keyStates['w']) { pointB.y += delta; }


	glutPostRedisplay();
}

void lineSegment(void)
{

	keyOperations();
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_LINES);
	glVertex2f(pointA.x, pointA.y);
	glVertex2f(pointB.x, pointB.y);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowPosition(50, 100);

	glutInitWindowSize(400, 300);

	glutCreateWindow("multiple key press");

	init();

	glutDisplayFunc(lineSegment);

	glutKeyboardFunc(keyPressed);

	glutKeyboardUpFunc(keyUp);

	glutMainLoop();

	return 0;
}


