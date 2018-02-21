#include <GL/glut.h>					// (or others, depending on the system in use)
#include "bevgrafmath2017.h"
//#include <math.h>
#include <iostream>
#include <time.h>

int winWidth = 400, winHeight =400;
float delta = 1;
float r=20;
GLint keyStates[256];
vec2 irany;
vec2 O;
vec2 food;
int recurse = 0;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
    glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
    srand (time(NULL));
    O={(rand() % (winWidth-int(2*r)))+r,(rand() % (winHeight-int(2*r)))+r};
    irany={float(rand() % 9 - 4)-0.5f,float(rand() % 9 - 4)-0.5f};
    if (rand() % 2){
        food={(rand() % int(O.x-r)),(rand() % int(O.y-r))};
    } else {
        food={(rand() % int(winWidth-O.x-r) + O.x+r),(rand() % int(winHeight-O.y-r) + O.y+r)};
    }
}

void getfood(vec2 food){
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
		glVertex2d(food.x,food.y);
	glEnd();
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
        if (rand() % 2){
            food={(rand() % int(O.x-r)),(rand() % int(O.y-r))};
        } else {
            food={(rand() % int(winWidth-O.x-r) + O.x+r),(rand() % int(winHeight-O.y-r) + O.y+r)};
        }
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
        r=r+3;
        /*if (O.x<r && O.y<r){
            O.x=r+1;
            O.y=r+1;
        }
        if (O.x>winWidth-r && O.y>winHeight-r){
            O.x=winWidth-r-1;
            O.y=winHeight-r-1;
        }
        if (O.x<r && O.y>winHeight-r){
            O.x=r+1;
            O.y=winHeight-r-1;
        }
        if (O.y<r && O.x>winWidth-r){
            O.y=r+1;
            O.x=winWidth-r-1;
        }*/
        if (O.x<r) O.x=r+1;
        if (O.y<r) O.y=r+1;
        if (O.x>winWidth-r) O.x=winWidth-r-1;
        if (O.y>winHeight-r) O.y=winHeight-r-1;
        }
    } else {
        if (recurse==1){
            if (rand() % 2){
                food={(rand() % int(O.x-r)),(rand() % int(O.y-r))};
            } else {
                food={(rand() % int(winWidth-O.x-r) + O.x+r),(rand() % int(winHeight-O.y-r) + O.y+r)};
            }
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
            r=r+3;
            /*if (O.x<r && O.y<r){
                O.x=r+1;
                O.y=r+1;
            }
            if (O.x>winWidth-r && O.y>winHeight-r){
                O.x=winWidth-r-1;
                O.y=winHeight-r-1;
            }
            if (O.x<r && O.y>winHeight-r){
                O.x=r+1;
                O.y=winHeight-r-1;
            }
            if (O.y<r && O.x>winWidth-r){
                O.y=r+1;
                O.x=winWidth-r-1;
            }*/
            if (O.x<r) O.x=r+1;
            if (O.y<r) O.y=r+1;
            if (O.x>winWidth-r) O.x=winWidth-r-1;
            if (O.y>winHeight-r) O.y=winHeight-r-1;
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
	if (keyStates['a']) { O.x -= delta; }
	if (keyStates['d']) { O.x += delta; }

	if (keyStates['s']) { O.y -= delta; }
	if (keyStates['w']) { O.y += delta; }
    
    if (keyStates['n']) { irany.x=irany.x*-1; }
	if (keyStates['m']) { irany.y=irany.y*-1; }


	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'j':
        //if (keyStates[key])
            O.x -= delta;
		break;
	case 'l':
        //if (keyStates[key])
            O.x += delta;
		break;
	case 'k':
        //if (keyStates[key])
            O.y -= delta;
		break;
	case 'i':
        //if (keyStates[key])
            O.y += delta;
		break;
    case 'n':
        //if (keyStates[key])
            irany.x=irany.x*-1;
		break;
	case 'm':
        //if (keyStates[key])
            irany.y=irany.y*-1;
		break;
	}
}


void draw()
{
	//keyOperations();
	
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.2f);
	
	circle(O, r);
    
    getfood(food); 

	glutSwapBuffers();
}

void bounce(){
    if (O.x<=r) irany.x=irany.x*-1;
    if (O.y>=winHeight-r) irany.y=irany.y*-1;
    if (O.x>=winWidth-r) irany.x=irany.x*-1;
    if (O.y<=r) irany.y=irany.y*-1;
}

void update(int n)
{
	std::cout<<food.x<<std::endl;
    std::cout<<food.y<<std::endl;

	glutPostRedisplay();

	glutTimerFunc(1, update, 0);
    
    O+=irany;
    
    bounce();
    
    eat();
    
    //std::cout<<keyStates['n']<<std::endl;

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(0, 0);   // Set top-left display-window position.
	glutInitWindowSize(400, 400);      // Set display-window width and height.
	glutCreateWindow("An Example OpenGL Program"); // Create display window.

	init();                            // Execute initialization procedure.
	glutDisplayFunc(draw);       // Send graphics to display window.
	glutTimerFunc(5, update, 0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();                    // Display everything and wait.
	return 0;
}