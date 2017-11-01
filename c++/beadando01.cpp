#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;

vec2 hermitePoints[4] = { {100, 300}, {200, 100}, {300, 200}, {400, 100} };
mat24 hermite={hermitePoints[0],hermitePoints[1],hermitePoints[2],hermitePoints[3]};
float t[3] = {-2.0,0.5,1.5};
vec4 mvectors[4] = {{pow(t[0],3.0),pow(t[0],2.0),t[0],1.0},{pow(t[1],3.0),pow(t[1],2.0),t[1],1.0},{pow(t[2],3.0),pow(t[2],2.0),t[2],1.0},{3*pow(t[0],2.0),2*t[0],1.0,0.0}};
mat4 mi = {mvectors[0],mvectors[1],mvectors[2],mvectors[3]};
mat4 m = transpose(inverse(mi));

GLint dragged = -1;

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

void display() {
	mat24 G={hermitePoints[0],hermitePoints[2],hermitePoints[3],hermitePoints[1]-hermitePoints[0]};
	GLint i;
	float j;
	glClear(GL_COLOR_BUFFER_BIT);

	/*glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 4; i++)
		glVertex2f(hermitePoints[i].x, hermitePoints[i].y);
	glEnd();*/
	
	mat24 C = G*m;
	
	glColor3f(0.0, 1.0, 0.0);
	
	glBegin(GL_LINE_STRIP);
	glVertex2f(hermitePoints[1].x,hermitePoints[1].y);
	for (j = -2.0; j < 1.5; j=j+0.01){
		vec4 thirdvector = {{pow(j,3)},{pow(j,2)},{j},{1}};
		vec2 qt = C*thirdvector;
		glVertex2f(qt.x, qt.y);
	}
	glEnd();

	
	glColor3f(1.0, 0.0, 0.0);
	
	glBegin(GL_POINTS);
	for (i = 0; i < 4; i++)
		glVertex2f(hermitePoints[i].x, hermitePoints[i].y);
	glEnd();

	glutSwapBuffers();
}

GLint getActivePoint(vec2 p[], GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p[i], P) < s)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		if ((i = getActivePoint(hermitePoints, 4, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		hermitePoints[dragged].x = xMouse;
		hermitePoints[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Gorbek");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutMainLoop();
	return 0;
}


