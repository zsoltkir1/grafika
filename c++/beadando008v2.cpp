#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>

GLsizei winWidth = 800, winHeight = 600;
mat4 w2v, projection, Mk, rotationZ, rotationX, rotationY;
GLint keyStates[256];
int N = 8,stateChange = 1;
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
vec2 drawableCube[8] = {};
GLfloat cX = winWidth / 2, cY = winHeight / 2, cW = 45.0f, cH = 45.0f;
float beta = 0.0, alpha = 0.0, gamma = 0.0, stepinterval = 0.05;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_STIPPLE);
	glPointSize(6.0);
    glLineWidth(3.0);
	//glLineStipple(1, 0xFF00);
    //initMatrices();
}

void initMatrices(){   
    rotationX = rotateX(alpha);
    rotationY = rotateY(beta);
    rotationZ = rotateZ(gamma);
	if (stateChange == 1) {
		projection = ortho();
	}
	else if (stateChange == 2) {
		projection = perspective(5.0);
	}
	w2v = windowToViewport3(vec2(-1.0f, -1.0f), vec2(1.0f, 1.0f), vec2(cX, cY), vec2(cW, cH));
}

void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

vec2 normalVector(vec2 point1,vec2 point2){
    float subx=point2.x-point1.x;
    float suby=point2.y-point1.y;
    float x=suby*-1;
    float y=subx;   
    vec2 point3={x,y};
    return point3;   
}

vec2 metszespont(vec2 point1, vec2 point2, vec2 point3, vec2 point4){
    vec2 egyenes1=normalVector(point1,point2);
    vec2 egyenes2=normalVector(point3,point4);
    float const1=egyenes1.x*point1.x+egyenes1.y*point1.y;
    float const2=egyenes2.x*point3.x+egyenes2.y*point3.y;
    float detfelcserelt1=(const1*egyenes2.y)-(egyenes1.y*const2);
    float detfelcserelt2=(egyenes1.x*const2)-(const1*egyenes2.x);
    float deteredeti=(egyenes1.x*egyenes2.y)-(egyenes1.y*egyenes2.x);
    if (deteredeti!=0){
        vec2 a;
        a.x=detfelcserelt1/deteredeti;
        a.y=detfelcserelt2/deteredeti;
        return a;
    }
    else {
        vec2 a={-500,-500};
        return a;
    }
}

void drawCube() {
	Mk = w2v *projection * rotationZ * rotationX * rotationY;
	for (int i = 0; i < N; i++) {
		vec4 pointH = ihToH(cube12[i]);
		vec4 transformedPoint = Mk*pointH;
		if (transformedPoint.w != 0)
		{
			vec3 res = hToIh(transformedPoint);
			if (res.z == 0) {
				drawableCube[i] = { res.x, res.y };
			}
		}
	}
	/*glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();*/
    
    /*glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();*/

    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 5; i++) {
        for (int j=0; j < 3; j++){
            if (drawableCube[cubefaces[i][j+1]].x<winWidth/2){
                glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
                glVertex2f(drawableCube[cubefaces[i][j+1]].x, drawableCube[cubefaces[i][j+1]].y);
            }
        }
	}
	glEnd();
    
    
    /*glColor3f(1.0, 0.0, 0.0);
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
	glEnd();*/
}

void leptetes()
{
    if (keyStates['q']) {
		//cout << "a: " << beta <<endl;
		beta -= stepinterval;
	}
	if (keyStates['e']) {
		//cout << "d: " << beta << endl;
		beta += stepinterval;
	}
	//cout << "BBB" << endl;
	if (keyStates['a']) {
		//cout << "a: " << beta <<endl;
		alpha -= stepinterval;
	}
	if (keyStates['d']) {
		//cout << "d: " << beta << endl;
		alpha += stepinterval;
	}
	if (keyStates['w']) {
		gamma += stepinterval;
		//cout << "w: " << alpha << endl;
	}
	if (keyStates['s']) {
		gamma -= stepinterval;
		//cout << "s: " << alpha << endl;
	}
	if (keyStates['r']) {
		stateChange = 1;
		//cout << "w: " << alpha << endl;
	}
	if (keyStates['t']) {
		stateChange = 2;
		//cout << "s: " << alpha << endl;
	}
	if (keyStates[27]) {
		exit(0);

	}

	glutPostRedisplay();
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        cX=xMouse;
        cY=winHeight-yMouse;
    }  
}

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
    
    initMatrices();
    drawCube();
    leptetes();
    
	glutSwapBuffers();
}

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
	//glutMouseFunc(processMouse);
	//glutMotionFunc(processMouseActiveMotion);
    glutMouseFunc(processMouse);
    glutTimerFunc(5, update, 0);
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}