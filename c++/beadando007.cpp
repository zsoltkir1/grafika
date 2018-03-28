#include <GL/glut.h>
#include <bevgrafmath2017.h>

GLint keyStates[256];

vec2 pointA = { 100, 40 };
vec2 pointB = { 200, 200 };

GLfloat delta = 1.0f;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = 0;
}

void keyOperations(int value)
{
	if (keyStates['a']) { pointA.x -= delta; }
	if (keyStates['d']) { pointA.x += delta; }

	if (keyStates['s']) { pointB.y -= delta; }
	if (keyStates['w']) { pointB.y += delta; }

	glutPostRedisplay();
	
	glutTimerFunc(5, keyOperations, 0);
}

void fuggveny1(){
	glColor3f(1.0, 0.0, 0.0);
	mat3 w2w=windowToViewport2(vec2(-2,-2), vec2(4,4), vec2(0,300), vec2(400,400));
	glBegin(GL_LINE_STRIP);
	for (float i=-1;i<=1;i=i+0.01f){
		vec3 p={i,pow(i,3.0f),1};
		p=w2w*p;
		glVertex2f(p.x, p.y);    
	}
	glEnd();
}

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
    fuggveny1();	
    
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("multiple key press");

	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(5, keyOperations, 0);
	glutMainLoop();

	return 0;
}


