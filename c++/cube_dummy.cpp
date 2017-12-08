#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <math.h>

GLsizei winWidth = 800, winHeight = 800;

struct faces4 {
	int p[4];
	vec3 normal;
};

int N = 8;
vec3 cube[8] = { };
vec2 drawableCube[8] = {};

int cubefaces[6][4] = {
	{ 0,1,2,3 },
	{ 1,5,6,2 },
	{ 5,4,7,6 },
	{ 4,0,3,7 },
	{ 7,6,2,3 },
	{ 4,1,5,0 }
};
vec3 cube12[8] = {
	{ -1,-1,1 },//0
	{ 1,-1,1 }, //1
	{ 1,1,1 },	//2
	{ -1,1,1 }, //3
	{ -1,-1,-1 },//4
	{ 1,-1,-1 }, //5
	{ 1,1,-1 },  //6
	{ -1,1,-1 }, //7
};

mat4 w2v, projection;
float alpha = 0;
float beta = 0;


void initMatrices(){

	projection = ortho();
    
    vec2 windowSize = {10, 10};
    vec2 windowPosition = { -5, -5 };
    vec2 viewportSize = { 450, 450};
    vec2 viewportPosition = { winWidth / 2 - viewportSize.x / 2, winHeight / 2 - viewportSize.y / 2 };
    w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    glLineWidth(1.0);
    
    initMatrices();
}

void drawCube(){
    
    /*glBegin(GL_POINTS);
    for (int i = 0; i < N; i++){
		
    }
    glEnd();

	glBegin(GL_LINES);

	glEnd();*/
    
    
    
    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();
	glColor3f(1.000, 0.271, 0.000);
	glBegin(GL_POINTS);
	for (int i = 1; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < N / 2; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = (N / 2); i < N; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < (N / 2); i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
		glVertex2f(drawableCube[i + 4].x, drawableCube[i + 4].y);
	}
	glEnd();

    
    
}

/*void transform(){
	mat4 rotation = ;
    mat4 M = w2v * projection * rotation;

    for ( int i = 0; i < N; i++ ){
        
		vec4 pointH = ;
		vec4 transformedPoint = ;

		if (transformedPoint.w != 0) 
		{
			drawableCube[i] = {  };
		}
        
    }
    
}
*/
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawCube();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'w':
	
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pyramid");
    
    init();
    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}




