#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256];
vec2 points[11] = { {10, 500}, {20, 590}, {300, 500}, {520, 450}, {0, 0}, {600, 300}, {300, 350}, {0, 0}, {100, 200}, {200, 100}, {350, 150} };
vec2 decastPoints[5][5];
float u = 0.5;
mat24 hermite={points[0],points[1],points[2],points[3]};
float t[3] = {-2.0,0.5,1.5};
vec4 mvectors[4] = {{pow(t[0],3.0),pow(t[0],2.0),t[0],1.0},{pow(t[1],3.0),pow(t[1],2.0),t[1],1.0},{pow(t[2],3.0),pow(t[2],2.0),t[2],1.0},{3*pow(t[0],2.0),2*t[0],1.0,0.0}};
mat4 mi = {mvectors[0],mvectors[1],mvectors[2],mvectors[3]};
mat4 m = transpose(inverse(mi));

GLint dragged = -1;

int factorial(int f) {
	int factorial = 1;
	for (int i = 1; i <= f; i++) {
		factorial *= i;
	}
	return factorial;
}

void changeu() {
	if (keyStates['a'] && u >= 0.01) {
		u -= 0.01;
	}
	else if (keyStates['d'] && u <= 0.99) {
		u += 0.01;
	}
	else if (keyStates[27]) {
		exit(0);

	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
	glLineWidth(1.0);
}

void display() {
	changeu();
	points[7] = points[6] + (0.75)*(points[6] - points[5]);
	for (int caste = 0;caste < 5; caste++)
	decastPoints[0][caste] = points[caste+6];
	int masodikBezierhossz = 5;
	for (int gen = 1; gen <= masodikBezierhossz-1; gen++) 
		for (int i = 0; i <= (masodikBezierhossz - 1) - gen; i++) 
			decastPoints[gen][i] = (1 - u)*decastPoints[gen - 1][i] + u*decastPoints[gen - 1][i + 1];
		
	
	mat24 G={points[0],points[2],points[3],points[1]-points[0]};
	mat24 C = G*m;
	
	vec4 derivaltmatrix = {3*pow(t[2],2.0),2*t[2],1,0};
	vec2 e2 = C*derivaltmatrix;
	points[4]=points[3]+(e2/3.0);
	vec2 masodiknemmozgathato=points[3]+(e2);
	GLint i;
	float j;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.0, 1.0, 0.0);
	
	
	glBegin(GL_LINE_STRIP);
	glVertex2f(points[1].x,points[1].y); //valahol el kell kezdődjön
	for (j = -2.0; j < 1.5; j=j+0.01){
		vec4 thirdvector = {{pow(j,3)},{pow(j,2)},{j},{1}};
		vec2 qt = C*thirdvector;
		glVertex2f(qt.x, qt.y);
	} //eddig tartott a hermite....

	for (j = 0; j < 1; j=j+0.01){
		vec2 bernstein = {0.0,0.0};
		int bernsteinStart = 3;
		int n = 4;
		for (i = 3; i < 7; i++){
			bernstein += points[i]*(factorial(n-1) / (factorial(i-bernsteinStart)*factorial((n-1) - (i-bernsteinStart)))*pow(j, (i-bernsteinStart))*pow((1 - j), ((n-1) - (i-bernsteinStart))));
		}
		glVertex2f(bernstein.x, bernstein.y);
	} //eddig tartott az első bezier 
	
	glEnd();
	//innentol indul a 2. bezier
	for (int gen = 1; gen <= masodikBezierhossz; gen++){
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= (masodikBezierhossz - 1) - gen; i++)
			glVertex2f(decastPoints[gen][i].x, decastPoints[gen][i].y);
		glEnd();
	}
	
	
	
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(points[3].x, points[3].y);
	//glVertex2f(points[4].x, points[4].y); //ezt full felesleges ideírni
	glVertex2f(masodiknemmozgathato.x, masodiknemmozgathato.y);
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (i = 4; i < 11; i++)
	glVertex2f(points[i].x, points[i].y);
	glEnd();
	

	
	glColor3f(1.0, 0.0, 0.0);
	
	glBegin(GL_POINTS);
	for (i = 0; i < 7; i++){
		if (i==4) glColor3f(0.0, 0.0, 0.1);
		else glColor3f(1.0, 0.0, 0.0);
		glVertex2f(points[i].x, points[i].y);
	}
	glColor3f(0.0, 0.0, 0.1);
	glVertex2f(masodiknemmozgathato.x, masodiknemmozgathato.y);
	for (i = 0; i < 5; i++){
		if (i==1) glColor3f(0.0, 0.0, 0.1);
		else glColor3f(1.0, 0.0, 0.0);
		glVertex2f(decastPoints[0][i].x,decastPoints[0][i].y);
	}
	glColor3f(0.0, 0.3, 0.1);
	for (int gen = 1; gen <= masodikBezierhossz; gen++)
		for (int i = 0; i <= (masodikBezierhossz - 1) - gen; i++)
			glVertex2f(decastPoints[gen][i].x, decastPoints[gen][i].y);
	glEnd();
	
	//ez meg a görbe
	glBegin(GL_LINE_STRIP);
	for (float u = 0.0; u < 1.0; u += 0.01) {
		for (int gen = 1; gen <= masodikBezierhossz; gen++) {
			for (int i = 0; i <= (masodikBezierhossz - 1) - gen; i++) {
				decastPoints[gen][i] = (1 - u)*decastPoints[gen - 1][i] + u*decastPoints[gen - 1][i + 1];
			}
		}
		glVertex2f(decastPoints[4][0].x, decastPoints[4][0].y);
	}
	glEnd();
	//gorbevege

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
		if ((i = getActivePoint(points, 11, 3, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 0) {
		points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
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
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}


