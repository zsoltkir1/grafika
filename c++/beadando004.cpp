#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>

float winWidth = 800, winHeight = 600;

std::vector<vec2> points;
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

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);

    if (points.size()==4){
        glBegin(GL_LINE_STRIP);
        for (i = 0; i < points.size(); i++)
            glVertex2f(points[i].x, points[i].y);
        glEnd();
    }

	glColor3f(1.0, 0.0, 0.0);

    if (points.size()>0){
        glBegin(GL_POINTS);
        for (i = 0; i < points.size(); i++)
            glVertex2f(points[i].x, points[i].y);
        glEnd();
    }
    
	glutSwapBuffers();
}

/*GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p[i], P) < s)
			return i;
	return -1;
}*/

/*GLint getActivePoint2(vec2 *p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i;
	for (i = 0; i < size; i++)
		if (fabs((*(p + i)).x - x) < sens && fabs((*(p + i)).y - y) < sens)
			return i;
	return -1;
}*/

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	//GLint i;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && points.size()<4){
        vec2 pont={float(xMouse), winHeight - float(yMouse)};
        points.push_back(pont);
    }
	/*if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		if ((i = getActivePoint1(points, 4, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
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

	glutTimerFunc(10, update, 0);
    
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


