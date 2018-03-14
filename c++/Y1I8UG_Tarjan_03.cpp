#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>

float winWidth = 800, winHeight = 600;
std::vector<vec2> cannonballs1;
std::vector<vec2> cannonballs2;
std::vector<vec2> cannonballdirection;

vec2 irany;
vec2 O;
float kisr=20,nagyr=50;
float mx,my,alpha=0.05;
bool go=false;
GLint keyStates[256];


void initPoints(){
    alpha=0.05;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    mx=winWidth/2;
    my=500;
    O={400,500};
    irany={1,0};
    cannonballs2.clear();
    cannonballdirection.clear();
    cannonballs1.clear();
    
    for (float i=0; i<=6; i++){   
        for (float j=6; j>=i; j--){
            cannonballs1.push_back({winWidth-(6-j)*11-5,11*i+5});    
        }
    } 
    for (float i=0; i<=6; i++){   
        for (float j=6; j>=i; j--){
            cannonballs1.push_back({(6-j)*11+5,11*i+5});    
        }
    }
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
    glLineWidth(3.0);
    initPoints();
    srand (time(NULL));
}

void tar(){
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    if (cannonballs1.size()>0){        
        for (int i=0; i<cannonballs1.size(); i++){   
                glVertex2f(cannonballs1[i].x, cannonballs1[i].y);    
        }
    }
    glEnd();
}

void lovegtorony(){
    glLineWidth(3.0);
    
	glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
	glVertex2d(winWidth/2-50,0);
    glVertex2d(winWidth/2-50,50);
    glVertex2d(winWidth/2+50,50);
    glVertex2d(winWidth/2+50,0);
    glEnd();
    glColor3f(0.1, 0.1, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(winWidth/2-50,0);
    glVertex2d(winWidth/2-50,50);
    glVertex2d(winWidth/2+50,50);
    glVertex2d(winWidth/2+50,0);
    glEnd();
}

vec2 normalVector(vec2 point1,vec2 point2){
    float subx=point2.x-point1.x;
    float suby=point2.y-point1.y;
    float x=suby*-1;
    float y=subx;   
    vec2 point3={x,y};
    return point3;  
}

vec2 iranyVector(vec2 point1,vec2 point2){
    float subx=point2.x-point1.x;
    float suby=point2.y-point1.y; 
    vec2 point3={subx,suby};
    return point3;  
}

void agyu(){
    vec2 mouse={mx,winHeight-my};
    vec2 base={winWidth/2,50};
    vec2 egyenes=iranyVector(base,mouse);
    vec2 agyucso=egyenes;
    agyucso=normalize(agyucso);
    agyucso=agyucso*100;
    glLineWidth(20.0);
    glColor3f(0.0, 0.1, 0.0);
    glBegin(GL_LINES);
    glVertex2d(base.x,base.y);
    glVertex2d(base.x+agyucso.x,base.y+agyucso.y);
    glEnd();
}

void elipsisSemiCircle() {
	
    glLineWidth(3.0);
    
	glBegin(GL_POLYGON);
    glColor3f(1.0-alpha, 0.0, 0.0);
	for (float t = 0; t <=  2*pi(); t += 0.01){
        vec2 korpont={O.x + nagyr * cos(t),O.y + kisr * sin(t)};
        korpont=korpont+irany;
		glVertex2d(korpont.x,korpont.y);
    }
    glEnd();
    glColor3f(0.0, 0.1, 0.0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <=  2*pi(); t += 0.01){
        vec2 korpont={O.x + nagyr * cos(t),O.y + kisr * sin(t)};
        korpont=korpont+irany;
		glVertex2d(korpont.x,korpont.y);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(1.0-alpha, 0.0, 0.0);
    for (float t = 0; t <=  pi(); t += 0.01){
        vec2 korpont={O.x + kisr * cos(t),O.y+kisr + kisr * sin(t)};
        korpont=korpont+irany;
		glVertex2d(korpont.x,korpont.y);
    }
	glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.1, 0.0);
    for (float t = 0; t <=  pi(); t += 0.01){
        vec2 korpont={O.x + kisr * cos(t),O.y+kisr + kisr * sin(t)};
        korpont=korpont+irany;
		glVertex2d(korpont.x,korpont.y);
    }
    glEnd();
}

void updatefire(){
    if (cannonballs2.size()>0){
        glColor3f(0.0, 0.0, 1.0);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        for (int i=0;i<=cannonballs2.size()-1;i++){
            if (go) cannonballs2[i]+=cannonballdirection[i]*5;
            glVertex2d(cannonballs2[i].x,cannonballs2[i].y);
        }
        glEnd();
    }
}

void deletefire(){
    if (cannonballs2.size()>0){
        for (int i=0;i<cannonballs2.size();i++){
            if (cannonballs2[i].x<0 || cannonballs2[i].x>winWidth || cannonballs2[i].y>winHeight || cannonballs2[i].y<0){
            cannonballs2.erase(cannonballs2.begin()+i,cannonballs2.begin()+i+1);
            cannonballdirection.erase(cannonballdirection.begin()+i,cannonballdirection.begin()+i+1);
            }
            float tavolsagelipszis=((O.x-cannonballs2[i].x)*(O.x-cannonballs2[i].x))/(nagyr*nagyr)+((O.y-cannonballs2[i].y)*(O.y-cannonballs2[i].y))/(kisr*kisr);
            float tavolsagkor=((O.x-cannonballs2[i].x)*(O.x-cannonballs2[i].x))/(kisr*kisr)+((O.y+kisr-cannonballs2[i].y)*(O.y+kisr-cannonballs2[i].y))/(kisr*kisr);
            if (tavolsagkor<=1 || tavolsagelipszis<=1){
                cannonballs2.erase(cannonballs2.begin()+i,cannonballs2.begin()+i+1);
                cannonballdirection.erase(cannonballdirection.begin()+i,cannonballdirection.begin()+i+1);
                alpha+=0.05;
                if (irany.x<0) irany.x-=1;
                else irany.x+=1;
            }
        }
    }
}

void endgame(){
    if (go){
        if (irany.x>10 || irany.x<-10){
            glClearColor(0.0, 1.0, 0.0, 0.0);
            go=false;
        }
        if (cannonballs1.empty()){
            if (cannonballs2.empty()){
                glClearColor(1.0, 0.0, 0.0, 0.0);
                go=false;
            }
        }
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
        if (go==false){
            go=true;
            initPoints();
        }       
	}
}

void display() {

	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
    
    endgame();
    
    keyOperations();
    
    agyu();
    
    lovegtorony();
    
    tar();
    
    updatefire();
    
    if (go) deletefire();
    
    
    glColor3f(0.0f, 0.4f, 0.2f);
	
	elipsisSemiCircle();
    
	glutSwapBuffers();
}

void fire(){
    vec2 mouse={mx,winHeight-my};
    vec2 base={winWidth/2,50};
    vec2 egyenes=iranyVector(base,mouse);
    vec2 agyucso=egyenes;
    agyucso=normalize(agyucso);
    glLineWidth(20.0);
    cannonballs2.push_back({base.x,base.y});
    cannonballdirection.push_back({agyucso.x,agyucso.y});
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	if (go && button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && cannonballs1.size()>=1){
        cannonballs1.pop_back();
        fire();
    }  
}

void processMouse2(GLint xMouse, GLint yMouse) {
	if (go){
        mx=xMouse;
        my=yMouse;
    }    
}

void bounce(){
    if (O.x<=nagyr) irany.x=irany.x*-1;
    if (O.x>=winWidth-nagyr) irany.x=irany.x*-1;
}

void update(int n)
{
    if (go) O+=irany;
    
    bounce();
    
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
    glutPassiveMotionFunc(processMouse2);
    glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
    glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


