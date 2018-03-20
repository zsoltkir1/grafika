#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>

float winWidth = 800, winHeight = 600;

std::vector<vec2> points;
GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }
float t[4] = {-1.0,0.0,1.0,2.0};
vec4 mvectors[4] = {{pow(t[0],3.0f),pow(t[0],2.0f),t[0],1.0f},{pow(t[1],3.0f),pow(t[1],2.0f),t[1],1.0f},{pow(t[2],3.0f),pow(t[2],2.0f),t[2],1.0f},{pow(t[3],3.0f),pow(t[3],2.0f),t[3],1.0f}};
mat4 mi = {mvectors[0],mvectors[1],mvectors[2],mvectors[3]};
mat4 m = transpose(inverse(mi));
bool go = false;
GLint keyStates[256];
vec4 derivaltvec[4]={{3*pow(t[0],2.0f),2*t[0],1.0f,0.0f},{3*pow(t[1],2.0f),2*t[1],1.0f,0.0f},{3*pow(t[2],2.0f),2*t[2],1.0f,0.0f},{3*pow(t[3],2.0f),2*t[3],1.0f,0.0f}};
mat4 erintov ={derivaltvec[0],derivaltvec[1],derivaltvec[2],derivaltvec[3]};
mat4 erinto = transpose(inverse(erintov));
float gorbeut=-1.0;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_STIPPLE);
	glPointSize(10.0);
	glLineWidth(5.0);
	glLineStipple(1, 0xFF00);
}

void palcikaember() {
	GLfloat j;
	mat24 G={points[0],points[1],points[2],points[3]};
	mat24 C = G*m;
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINES);
    vec4 derivaltmatrix = {3*pow(gorbeut,2.0f),2*gorbeut,1,0};
    vec4 thirdvector = {{pow(gorbeut,3.0f)},{pow(gorbeut,2.0f)},{gorbeut},{1}};
    vec2 iranyElsolab = C*derivaltmatrix;
    vec2 qt2 = C*thirdvector;
    iranyElsolab=normalize(iranyElsolab)*25;
    vec2 elsolab={-iranyElsolab.y+qt2.x,iranyElsolab.x+qt2.y};
    glVertex2f(elsolab.x, elsolab.y);
    glVertex2f(qt2.x, qt2.y);
   
    /*thirdvector = {{pow((gorbeut+0.1f),3.0f)},{pow((gorbeut+0.1f),2.0f)},{(gorbeut+0.1f)},{1}};
    vec2 masodiklab={-iranyElsolab.y+qt2.x, iranyElsolab.x+qt2.y};
    glVertex2f(masodiklab.x, masodiklab.y);
    qt2 = C*thirdvector;
    glVertex2f(qt2.x, qt2.y); 
    
    //glVertex2f(qt2.x, qt2.y);  
    glVertex2f(masodiklab.x, masodiklab.y); 
    derivaltmatrix = {3*pow(gorbeut,2.0f),2*gorbeut,1.0f,0};
    thirdvector = {{pow(gorbeut,3.0f)},{pow(gorbeut,2.0f)},{gorbeut},{1}};
    vec2 qt = C*derivaltmatrix;
    qt=normalize(qt)*40;
    qt2 = C*thirdvector;
    vec2 test={-qt.y+qt2.x, qt.x+qt2.y};
    glVertex2f(test.x, test.y);*/
    glEnd();
    glBegin(GL_POINTS);
    glVertex2f(elsolab.x, elsolab.y);
    glEnd();
}

/*glBegin(GL_LINES);
    vec4 derivaltmatrix = {3*pow(gorbeut,2.0f),2*gorbeut,1,0};
    vec4 thirdvector = {{pow(gorbeut,3.0f)},{pow(gorbeut,2.0f)},{gorbeut},{1}};
    vec2 iranyElsolab = C*derivaltmatrix;
    vec2 qt = C*thirdvector;
    iranyElsolab=normalize(iranyElsolab)*25;
    vec2 elsolab={-iranyElsolab.y+qt.x,iranyElsolab.x+qt.y};
    glVertex2f(elsolab.x, elsolab.y);
    glVertex2f(iranyElsolab.x, iranyElsolab.y);
   
    thirdvector = {{pow((gorbeut+0.1f),3.0f)},{pow((gorbeut+0.1f),2.0f)},{(gorbeut+0.1f)},{1}};
    vec2 masodiklab={-qt.y+iranyElsolab.x, qt.x+iranyElsolab.y};
    glVertex2f(masodiklab.x, masodiklab.y);
    vec2 iranyMasodiklab = C*thirdvector;
    glVertex2f(iranyMasodiklab.x, iranyMasodiklab.y); 
    
    //glVertex2f(qt2.x, qt2.y);  
    /*glVertex2f(masodiklab.x, masodiklab.y); 
    derivaltmatrix = {3*pow(gorbeut,2.0f),2*gorbeut,1.0f,0};
    thirdvector = {{pow(gorbeut,3.0f)},{pow(gorbeut,2.0f)},{gorbeut},{1}};
    qt = C*derivaltmatrix;
    qt=normalize(qt)*40;
    qt2 = C*thirdvector;
    vec2 test={-qt.y+qt2.x, qt.x+qt2.y};
    glVertex2f(test.x, test.y);
    glEnd();*/

void display() {
	GLint i;
	GLfloat j;
	glClear(GL_COLOR_BUFFER_BIT);
	

	

    if (points.size()==4){
		mat24 G={points[0],points[1],points[2],points[3]};
		mat24 C = G*m;
		//vec4 derivaltmatrix = {3*pow(t[2],2.0),2*t[2],1,0};
		//vec2 e2 = C*derivaltmatrix;
		palcikaember();
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (j = -1.0; j < 2.0; j=j+0.01){
			vec4 thirdvector = {{pow(j,3.0f)},{pow(j,2.0f)},{j},{1}};
			vec2 qt = C*thirdvector;
			glVertex2f(qt.x, qt.y);
		}
		glEnd();
		
        /*glBegin(GL_LINE_STRIP);
        for (i = 0; i < points.size(); i++)
            glVertex2f(points[i].x, points[i].y);
        glEnd();*/
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

GLint getActivePoint1(std::vector<vec2> p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p[i], P) < s)
			return i;
	return -1;
}

/*GLint getActivePoint2(vec2 *p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i;
	for (i = 0; i < size; i++)
		if (fabs((*(p + i)).x - x) < sens && fabs((*(p + i)).y - y) < sens)
			return i;
	return -1;
}*/

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && points.size()<4){
        vec2 pont={float(xMouse), winHeight - float(yMouse)};
        points.push_back(pont);
    }
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && points.size()==4)
		if ((i = getActivePoint1(points, 4, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP && points.size()==4)
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

void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void keyOperations() {
    if (keyStates['n'] ) { 
        if ((!go) && (points.size()==4)){
            go=true;
        }       
	}
}

void update(int n)
{   
    keyOperations();
    
    if (go){
        gorbeut+=0.01;
    }

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
	glutMotionFunc(processMouseActiveMotion);
    glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
    glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


