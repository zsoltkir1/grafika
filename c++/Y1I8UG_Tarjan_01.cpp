#include <GL/glut.h>					// (or others, depending on the system in use)
#include "bevgrafmath2017.h"
//#include <math.h>
#include <iostream>
#include <time.h>

float winWidth = 800, winHeight =800;
float delta = 1;
float r=50;
GLint keyStates[256],disabledKeyStates[256];
vec2 irany;
vec2 O;
vec2 food,tempfood;
int recurse = 0;

void getfood(vec2 food){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
		glVertex2d(food.x,food.y);
	glEnd();
}


void generatefood(){
	food={(rand() % int(winWidth)),(rand() % int(winHeight))};
	if (!((food.x>O.x+r) or (food.x<O.x-r)) and ((food.y>O.y+r) or (food.y<O.y-r))){
		generatefood();
	}
}

void circle(vec2 O, float r) {
	
	glBegin(GL_LINE_STRIP);
	for (float t = 0; t <=  2*pi(); t += 0.01){
        vec2 korpont={O.x + r * cos(t),O.y + r * sin(t)};
        korpont=korpont+irany;
		glVertex2d(korpont.x,korpont.y);
    }
	glEnd();
}


void eat(){
    if (dist(food,O)<=r){
        recurse=1;
        generatefood();
        if ((food.x < r) &&(food.y > winHeight-r)){
            eat();
        }
        else if ((food.x > winWidth-r) &&(food.y > winHeight-r)) {
            eat();
        }
        else if ((food.x < r) &&(food.y < r)) {
            eat();
        }
        else if ((food.x > winWidth-r) &&(food.y < r)) {
            eat();
        }
        else {
        getfood(food);
        recurse=0;
        r=r+10;
		if (r==150) exit(0);
        if (O.x<=r) O.x=r+1;
        if (O.y<=r) O.y=r+1;
        if (O.x>=winWidth-r) O.x=winWidth-r-1;
        if (O.y>=winHeight-r) O.y=winHeight-r-1;
        }
    } else {
        if (recurse==1){
            generatefood();
            if ((food.x < r) &&(food.y > winHeight-r)){
                eat();
            }
            else if ((food.x > winWidth-r) &&(food.y > winHeight-r)) {
                eat();
            }
            else if ((food.x < r) &&(food.y < r)) {
                eat();
            }
            else if ((food.x > winWidth-r) &&(food.y < r)) {
                eat();
            }
            else {
            getfood(food);
            recurse=0;
            r=r+10;
			if (r==150) exit(0);
            if (O.x<=r) O.x=r+1;
            if (O.y<=r) O.y=r+1;
            if (O.x>=winWidth-r) O.x=winWidth-r-1;
            if (O.y>=winHeight-r) O.y=winHeight-r-1;
            }
        } 
    }
}

void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = 0;
	disabledKeyStates[key] = 0;
}

void keyOperations() {

    if (keyStates['n'] and (((O.x-r)>0) or ((O.x+r)<winHeight))) { 
		if (!disabledKeyStates['n']) {
			irany.x=irany.x*-1;
			disabledKeyStates['n'] = 1;
		}	
	}
	if (keyStates['m'] and (((O.y-r)>0) or ((O.y+r)<winWidth))) { 
		if (!disabledKeyStates['m']) {
			irany.y=irany.y*-1;
			disabledKeyStates['m'] = 1;
		}
	}

}


void draw()
{	
	

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);
	
	circle(O, r);
    
    getfood(food); 

	keyOperations();
	
	glutSwapBuffers();
}

void bounce(){
    if (O.x<=r) irany.x=irany.x*-1;
    if (O.y>=winHeight-r) irany.y=irany.y*-1;
    if (O.x>=winWidth-r) irany.x=irany.x*-1;
    if (O.y<=r) irany.y=irany.y*-1;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 800.0);
    glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
    srand (time(NULL));
    O={((rand() % int(winWidth-2*r))+r),((rand() % int(winHeight-2*r))+r)};
    irany={float(rand() % 9 - 4)-0.5f,float(rand() % 9 - 4)-0.5f};
    generatefood();
}

void update(int n)
{
	glutPostRedisplay();

	glutTimerFunc(10, update, 0);
    
    O+=irany;
    
    bounce();
    
    eat();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(0, 0);   // Set top-left display-window position.
	glutInitWindowSize(800, 800);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	glutDisplayFunc(draw);       // Send graphics to display window.
	glutTimerFunc(5, update, 0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();                    // Display everything and wait.
	return 0;
}