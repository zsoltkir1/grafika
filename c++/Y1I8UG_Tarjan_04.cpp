#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>
#include <time.h>

float winWidth = 800, winHeight = 600;

std::vector<vec2> points;
std::vector<vec2> stars;
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
int timer=0;

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	//glEnable(GL_LINE_STIPPLE);
	glPointSize(6.0);
	glLineWidth(3.0);
	glLineStipple(1, 0xFF00);
    srand (time(NULL));
}

vec2 normalVector(vec2 point1,vec2 point2){
    float subx=point2.x-point1.x;
    float suby=point2.y-point1.y;
    float x=suby*-1;
    float y=subx;   
    vec2 point3={x,y};
    return point3;
    
}

void circle(vec2 O, float r) {
	
	glBegin(GL_LINE_STRIP);
	for (float t = 0; t <=  2*pi(); t += 0.01){
        vec2 korpont={O.x + r * cos(t),O.y + r * sin(t)};
		glVertex2d(korpont.x,korpont.y);
    }
	glEnd();
}

void csillagok(){
    stars.clear();
	for (int i=0;i<30;i++){
        vec2 csillag={(rand() % int(winWidth)),(rand() % int(winHeight/4))+3*int(winHeight/4)};
        stars.push_back(csillag);
    }
}

void palcikaember() {
    if (gorbeut<1.9){
        GLfloat j;
        mat24 G={points[0],points[1],points[2],points[3]};
        mat24 C = G*m;
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        vec4 derivaltmatrix = {3*pow(gorbeut,2.0f),2*gorbeut,1,0};
        vec4 tvector = {{pow(gorbeut,3.0f)},{pow(gorbeut,2.0f)},{gorbeut},{1}};
        vec2 iranyElsolab = C*derivaltmatrix;
        vec2 pontAGorben = C*tvector;
        iranyElsolab=normalize(iranyElsolab)*12.5f;
        vec2 dereka={-iranyElsolab.y+pontAGorben.x,iranyElsolab.x+pontAGorben.y};
        glVertex2f(dereka.x, dereka.y);
        glVertex2f(pontAGorben.x, pontAGorben.y);
          
        vec4 tvectorEltolva = {{pow((gorbeut+0.05f),3.0f)},{pow((gorbeut+0.05f),2.0f)},{(gorbeut+0.05f)},{1}};
        glVertex2f(dereka.x, dereka.y);
        pontAGorben = C*tvectorEltolva;
        glVertex2f(pontAGorben.x, pontAGorben.y);
        vec2 nyak={-iranyElsolab.y*1.5f+dereka.x,iranyElsolab.x*1.5f+dereka.y};
        glVertex2f(dereka.x, dereka.y);
        glVertex2f(nyak.x, nyak.y);
        
        vec2 kezIndul={-iranyElsolab.y+dereka.x,iranyElsolab.x+dereka.y};
        vec2 kez=normalVector(dereka,nyak);
        kez=-kez/2;
        kez=kez+kezIndul;
        glVertex2f(kezIndul.x, kezIndul.y);
        glVertex2f(kez.x,kez.y);
        
        vec2 fejkozeppont={-iranyElsolab.y/2.0f+nyak.x,iranyElsolab.x/2.0f+nyak.y};
        glEnd();
        float r=dist(fejkozeppont,nyak);
        circle(fejkozeppont,r);
    }
}

void haziko(){

    GLfloat j;
    mat24 G={points[0],points[1],points[2],points[3]};
    mat24 C = G*m;
    glColor3f(0.2, 0.6, 0.2);
    glBegin(GL_POLYGON);
    vec4 derivaltmatrix = {3*pow(2.0f,2.0f),2*2.0f,1,0};
    vec4 tvector = {{pow(2.0f,3.0f)},{pow(2.0f,2.0f)},{2.0f},{1}};
    vec2 iranyFal = C*derivaltmatrix;
    vec2 pontAGorben = C*tvector;
    vec4 tvector2 = {{pow(1.8f,3.0f)},{pow(1.8f,2.0f)},{1.8f},{1}};
    vec2 pontAGorben2 = C*tvector2;
    vec2 fal=normalVector(pontAGorben2,pontAGorben);
    fal=normalize(fal)*50+pontAGorben;
    
    glVertex2f(fal.x, fal.y); 
    glVertex2f(pontAGorben.x, pontAGorben.y);  
    glVertex2f(pontAGorben2.x,pontAGorben2.y);
    vec2 fal2=normalVector(pontAGorben2,pontAGorben);
    fal2=normalize(fal2)*50+pontAGorben2;
    glVertex2f(fal2.x,fal2.y);
    glEnd();
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(fal.x, fal.y);
    glVertex2f(fal2.x,fal2.y);
    vec2 triangleCap=normalVector(fal2,fal);
    vec2 felezopont=(fal+fal2)/2;
    triangleCap=normalize(triangleCap)*20+felezopont;
    glVertex2f(triangleCap.x,triangleCap.y);    
    glEnd();
    
    if (gorbeut>1.9){
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        vec2 ablakfal=normalVector(pontAGorben2,pontAGorben);
        tvector = {{pow(1.95f,3.0f)},{pow(1.95f,2.0f)},{1.95f},{1}};
        vec2 pontAGorbeMellett = C*tvector;
        vec2 ablakfalfelul=normalize(ablakfal)*40+pontAGorbeMellett;
        vec2 ablakfalalul=normalize(ablakfal)*20+pontAGorbeMellett;
        glVertex2f(ablakfalfelul.x,ablakfalfelul.y);
        glVertex2f(ablakfalalul.x,ablakfalalul.y);
        
        vec2 ablakfal2=normalVector(pontAGorben2,pontAGorben);
        tvector = {{pow(1.85f,3.0f)},{pow(1.85f,2.0f)},{1.85f},{1}};
        pontAGorbeMellett = C*tvector;
        vec2 ablakfalfelul2=normalize(ablakfal2)*40+pontAGorbeMellett;
        vec2 ablakfalalul2=normalize(ablakfal2)*20+pontAGorbeMellett;
        glVertex2f(ablakfalalul2.x,ablakfalalul2.y);
        glVertex2f(ablakfalfelul2.x,ablakfalfelul2.y);
        glEnd();
    }
}

void display() {
	GLint i;
	GLfloat j;
	glClear(GL_COLOR_BUFFER_BIT);
	

    if (points.size()==4){
		mat24 G={points[0],points[1],points[2],points[3]};
		mat24 C = G*m;    
        if (gorbeut>0.5){
            glColor3f(1.0, 1.0, 0.5);
            glBegin(GL_POINTS);
            for (int k=0;k<30;k++){
                glVertex2f(stars[k].x,stars[k].y);
            }
            glEnd();
        }
        
		palcikaember();
        haziko();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (j = -1.0; j < 2.0; j=j+0.01){
			vec4 tvector = {{pow(j,3.0f)},{pow(j,2.0f)},{j},{1}};
			vec2 qt = C*tvector;
			glVertex2f(qt.x, qt.y);
		}
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

GLint getActivePoint1(std::vector<vec2> p, GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p[i], P) < s)
			return i;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && points.size()<4){
        vec2 pont={float(xMouse), winHeight - float(yMouse)};
        points.push_back(pont);
    }
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && points.size()==4)
		if ((i = getActivePoint1(points, 4, 3, xMouse, winHeight - yMouse)) != -1)
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
//rgb(135,206,235)    
//rgb(72,61,139)
    glClearColor(0.5-(gorbeut/4), 0.7-(gorbeut/3), 1.0-(gorbeut/3.5), 0.0);
    
    if (timer==0) csillagok();

    keyOperations();
    
    timer+=1;
    
    if (timer==20 && gorbeut<2) timer=0;
    
    if ((go) && (gorbeut<2)){
        gorbeut+=0.01;
    }

	glutPostRedisplay();

	glutTimerFunc(50, update, 0);
    
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


