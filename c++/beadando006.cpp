#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>

GLsizei winWidth = 800, winHeight = 600;

vec2 points[4] = { {100, 300}, {200, 100}, {300, 200}, {400, 100} };
std::vector<vec2> squareCenters;
std::vector<double> squareSizes;


GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glPointSize(10.0);
	glLineWidth(5.0);
	glLineStipple(1, 0xFF00);
}

void drawSquare() {
	for (int i=0;i<squareCenters.size();i++){
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2f(squareCenters[i].x-squareSizes[i]/2, squareCenters[i].y-squareSizes[i]/2);
			glVertex2f(squareCenters[i].x-squareSizes[i]/2, squareCenters[i].y+squareSizes[i]/2);
			glVertex2f(squareCenters[i].x+squareSizes[i]/2, squareCenters[i].y+squareSizes[i]/2);
			glVertex2f(squareCenters[i].x+squareSizes[i]/2, squareCenters[i].y-squareSizes[i]/2);			
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
			glVertex2f(squareCenters[i].x-squareSizes[i]/2, squareCenters[i].y-squareSizes[i]/2);
			glVertex2f(squareCenters[i].x-squareSizes[i]/2, squareCenters[i].y+squareSizes[i]/2);
			glVertex2f(squareCenters[i].x+squareSizes[i]/2, squareCenters[i].y+squareSizes[i]/2);
			glVertex2f(squareCenters[i].x+squareSizes[i]/2, squareCenters[i].y-squareSizes[i]/2);			
		glEnd();
	}
}

void fillSquare(float x,float y) {
	squareCenters.push_back({x,y});
	squareSizes.push_back(50.0);
}

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquare();

	/*glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();*/
	
	

	glutSwapBuffers();
}


void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		fillSquare(xMouse,winHeight-yMouse);
	}
		
	/*if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;*/
}

/*void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}*/

void update(int n)
{   
	glutPostRedisplay();

	glutTimerFunc(30, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Drag & Drop");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	//glutMotionFunc(processMouseActiveMotion);
	glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


