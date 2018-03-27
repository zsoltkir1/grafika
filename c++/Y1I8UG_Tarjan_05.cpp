#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

GLint keyStates[256],keyStates2[256];
vec2 points[18] = { {50, 100}, {50, 120}, {50, 135}, {80, 135}, {110, 135}, {90, 160}, {110, 200}, {125, 240}, {250, 400}, {400, 350}, {550, 250}, {700,140}, {700,100}, {200,250}, {280,300}, {350,330}, {400,300}, {450,250} };
vec2 decastPoints[5][5];
float u = 0.5;
float t[3] = {-1.0,-0.5,1.0};
vec4 mvectors[4] = {{pow(t[0],3.0f),pow(t[0],2.0f),t[0],1.0f},{pow(t[1],3.0f),pow(t[1],2.0f),t[1],1.0f},{pow(t[2],3.0f),pow(t[2],2.0f),t[2],1.0f},{3*pow(t[2],2.0f),2*t[2],1.0f,0.0f}};
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
    if (keyStates2[key]) keyStates2[key] = 0;
    else keyStates2[key] = 1;
}
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}

void init() {
	glClearColor(0.4, 0.7, 0.8, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(6.0);
	glLineWidth(2.0);
}

void drawPoints(){
    if (keyStates2['p']){
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 18; i++) glVertex2f(points[i].x, points[i].y);
        glEnd();
    }
}

void drawDecasteljauLines(){
    if (keyStates2['m']){
        glColor3f(0.0, 0.0, 0.0);	 
        glBegin(GL_LINE_STRIP);
        for (int i = 13; i < 18; i++) glVertex2f(points[i].x, points[i].y);
        glEnd();
        for (int d = 0;d < 5; d++)
        decastPoints[0][d] = points[13+d];
        int bezierhossz = 5;
        for (int gen = 1; gen <= bezierhossz-1; gen++){ 
            glBegin(GL_LINE_STRIP);
            for (int i = 0; i <= (bezierhossz - 1) - gen; i++){ 
                decastPoints[gen][i] = (1 - u)*decastPoints[gen - 1][i] + u*decastPoints[gen - 1][i + 1];   
                glVertex2f(decastPoints[gen][i].x, decastPoints[gen][i].y);
            }
            glEnd();
        }
        vec2 pointInTheLine=(1.0 - u)*points[13] + u*points[17];
        glBegin(GL_POINTS);		
        glVertex2f(decastPoints[4][0].x, decastPoints[4][0].y);
        glVertex2f(pointInTheLine.x, pointInTheLine.y);
        glEnd();
    }
}

void drawLines(){
    if (keyStates2['n']){
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 13; i++) glVertex2f(points[i].x, points[i].y);
        glEnd();
    }
}

void drawBernsteinBezier(int start,int end, float red, float green, float blue, bool c1folytonosveg){
    glColor3f(red, green, blue);
    glBegin(GL_LINE_STRIP);
    int n = 3;
    for (float u = 0; u < 1; u=u+0.01){
		vec2 bernstein = {0.0,0.0};
		int bernsteinStart = start;
		for (int i = start; i <= end; i++){
			bernstein += points[i]*(factorial(n) / (factorial(i-bernsteinStart)*factorial(n - (i-bernsteinStart)))*pow(u, (i-bernsteinStart))*pow((1 - u), (n - (i-bernsteinStart))));
		}
		glVertex2f(bernstein.x, bernstein.y);
	}
    glEnd();
    if (c1folytonosveg) points[end+1] = points[end] + (points[end] - points[end-1]);
}

void drawHermite(){
    mat24 G={points[12],points[11],points[10],points[9]-points[10]};
	mat24 C = G*m;
    glColor3f(0.0, 1.0, 1.0);	
	glBegin(GL_LINE_STRIP);
	for (float j = t[0]; j < t[2]; j=j+0.01){
		vec4 thirdvector = {{pow(j,3.0f)},{pow(j,2.0f)},{j},{1}};
		vec2 qt = C*thirdvector;
		glVertex2f(qt.x, qt.y);
	}
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(points[9].x,points[9].y);
    glEnd();   
}

void drawDecasteljauBezier(){
    glColor3f(0.0, 1.0, 1.0);	
    
    int bezierhossz = 5;
    for (int d=0; d<5; d++){
        decastPoints[0][d]=points[13+d];
    }
    glBegin(GL_LINE_STRIP);
	for (float u = 0.0; u < 1.0; u += 0.01) {
		for (int gen = 1; gen <= bezierhossz; gen++) {
			for (int i = 0; i <= (bezierhossz - 1) - gen; i++) {
				decastPoints[gen][i] = (1 - u)*decastPoints[gen - 1][i] + u*decastPoints[gen - 1][i + 1];
			}
		}
		glVertex2f(decastPoints[4][0].x, decastPoints[4][0].y);
	}
	glEnd();
}

void drawTire(vec2 O, float r) {
	
    glColor3f(0.7,0.7,0.7);
	glBegin(GL_POLYGON);
	for (float t = 0; t <=  2*pi(); t += 0.01){
        vec2 korpont={O.x + r * cos(t),O.y + r * sin(t)};
		glVertex2d(korpont.x,korpont.y);
    }
	glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
	for (float t = 0; t <=  2*pi(); t += 2*pi()/10){
        vec2 korpont={O.x + r/1.5f * cos(t),O.y + r/1.5f * sin(t)};
		glVertex2d(korpont.x,korpont.y);
    }
	glEnd();
}

void drawTires(){
    vec2 tire1=(1.0 - (3.0/4.0))*points[12] + (3.0/4.0)*points[0];
    vec2 tire2=(1.0 - (1.0/4.0))*points[12] + (1.0/4.0)*points[0];
    drawTire(tire1,40);
    drawTire(tire2,40);
    
}

void drawGrass(){
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 80);
    glVertex2f(winWidth, 80);
    glVertex2f(winWidth, 0);
    glEnd();
}

void display() {
	changeu();
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrass();
    drawPoints();
    drawLines();
    drawBernsteinBezier(0,3,0.0,1.0,1.0,true);
    drawBernsteinBezier(3,6,1.0,0.0,1.0,true);
    drawBernsteinBezier(6,9,1.0,1.0,0.0,false);
    drawHermite();
    drawDecasteljauBezier();
    drawDecasteljauLines();
    drawTires();
    
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(points[0].x, points[0].y);
    glVertex2f(points[12].x, points[12].y);
    glVertex2f(points[13].x, points[13].y);
    glVertex2f(points[17].x, points[17].y);
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
		if ((i = getActivePoint(points, 18, 3, xMouse, winHeight - yMouse)) != -1)
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


