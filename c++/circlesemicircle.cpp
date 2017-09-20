#include <GL/glut.h>					// (or others, depending on the system in use)
#include <bevgrafmath2017.h>
#include <math.h>
#include <vector>

GLsizei winWidth = 800, winHeight = 600;

std::vector<std::vector<vec2>> objectsPoints;


void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.f, winWidth, 0.f, winHeight);
}

void semicircle(vec2 O, GLdouble r) {

	glBegin(GL_LINE_STRIP);
	for (GLdouble t = 0; t <= pi(); t += 0.01)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

void circle(vec2 O, GLdouble r) {

	glBegin(GL_LINE_LOOP);
	for (GLdouble t = 0; t <= 2 * pi(); t += 0.01)
		glVertex2d(O.x + r * cos(t), O.y + r * sin(t));
	glEnd();
}

void ellipse(vec2 O, GLdouble a, GLdouble b) {

	glBegin(GL_LINE_LOOP);
	for (GLdouble t = 0; t <= 2 * pi(); t += 0.01)
		glVertex2d(O.x + a * cos(t), O.y + b * sin(t));
	glEnd();
}

void semicircleWithVector(vec2 O, GLdouble r) {

	objectsPoints.push_back(std::vector<vec2>());
	for (GLdouble t = 0; t <= pi(); t += 0.01)
		objectsPoints.back().push_back(vec2(O.x + r * cos(t), O.y + r * sin(t)));
}

void circleWithVector(vec2 O, GLdouble r) {

	objectsPoints.push_back(std::vector<vec2>());
	for (GLdouble t = 0; t <= 2 * pi(); t += 0.01)
		objectsPoints.back().push_back(vec2(O.x + r * cos(t), O.y + r * sin(t)));
}

void ellipseWithVector(vec2 O, GLdouble a, GLdouble b) {

	objectsPoints.push_back(std::vector<vec2>());
	for (GLdouble t = 0; t <= 2 * pi(); t += 0.01)
		objectsPoints.back().push_back(vec2(O.x + a * cos(t), O.y + b * sin(t)));

}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);

	circle(vec2(100, 200), 30);

	semicircle(vec2(300, 100), 50);

	ellipse(vec2(200, 200), 25, 50);

	glFlush();
}

void setupForVectors() {
	circleWithVector(vec2(100, 200), 30);

	semicircleWithVector(vec2(300, 100), 50);

	ellipseWithVector(vec2(200, 200), 25, 50);
}

void drawWithVector() {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);

	glBegin(GL_LINE_STRIP);
		for (vec2 point : objectsPoints[0]) {
			glVertex2d(point.x, point.y);
		}
	glEnd();

	glBegin(GL_LINE_LOOP);
		for (vec2 point : objectsPoints[1]) {
			glVertex2d(point.x, point.y);
		}
	glEnd();

	glBegin(GL_LINE_LOOP);
		for (vec2 point : objectsPoints[2]) {
			glVertex2d(point.x, point.y);
		}
	glEnd();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);   // Set top-left display-window position.
	glutInitWindowSize(400, 300);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	setupForVectors();
	//glutDisplayFunc(draw);       // Send graphics to display window.
	glutDisplayFunc(drawWithVector);       // Send graphics to display window.
	glutMainLoop();                    // Display everything and wait.
	return 0;
}