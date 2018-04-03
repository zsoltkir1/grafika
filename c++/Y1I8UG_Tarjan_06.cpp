#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>
#include <time.h>

struct square {
	vec2 p[4];
    double r;
    double g;
    double b;
};

float winWidth = 800, winHeight = 600;
std::vector<square> squares;
std::vector<square> backSquares;
int vectorsize=0;
int vectorprinter=0;
float t = 0;
vec2 s = {1, 1};
int vecPosition = 0;

GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
    srand (time(NULL));
	glPointSize(10.0);
	glLineWidth(1.0);
	glLineStipple(1, 0xFF00);
}

void drawSquare() {
    t=0;
    s={1, 1};  
    vecPosition=vectorsize/90;
    for (int j=0;j<vecPosition;j++){
        for (int i=vectorprinter;i>j*90;i--){
            glColor3f(squares[i].r, squares[i].g, squares[i].b);
            glBegin(GL_POLYGON);
                glVertex2f(squares[i].p[0].x, squares[i].p[0].y);
                glVertex2f(squares[i].p[1].x, squares[i].p[1].y);
                glVertex2f(squares[i].p[2].x, squares[i].p[2].y);
                glVertex2f(squares[i].p[3].x, squares[i].p[3].y);			
            glEnd();
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(squares[i].p[0].x, squares[i].p[0].y);
                glVertex2f(squares[i].p[1].x, squares[i].p[1].y);
                glVertex2f(squares[i].p[2].x, squares[i].p[2].y);
                glVertex2f(squares[i].p[3].x, squares[i].p[3].y);		
            glEnd();
        }
    }
	
}

void fillSquare(float x,float y) {
    t=t-360/90;
    vectorsize+=90;
    backSquares.clear();
    square negyzet;
    negyzet.r=((double) rand() / (RAND_MAX));
    negyzet.g=((double) rand() / (RAND_MAX));
    negyzet.b=((double) rand() / (RAND_MAX));
    for (int i=0;i<90;i++){
        s.x=s.x+0.1;
        s.y=s.y+0.1;
        negyzet.p[0]={x-20.0/2,y-20.0/2};
        negyzet.p[1]={x-20.0/2,y+20.0/2};
        negyzet.p[2]={x+20.0/2,y+20.0/2};
        negyzet.p[3]={x+20.0/2,y-20.0/2};             
        for (int k=0;k<4;k++){
            vec2 center ={x,y};
            mat3 transToO = translate( -1 * center );
            mat3 rotated = rotate( t );
            mat3 scaled = scale ( s );
            mat3 transToC = translate( center );
            mat3 M = transToC * rotated * scaled * transToO;
            
            vec3 pointH = ihToH( negyzet.p[k] );
                vec3 rotatedPointH = M * pointH;
                if(rotatedPointH.z != 0){
                    vec2 result = hToIh(rotatedPointH);
                    negyzet.p[k] = { result.x, result.y  };
                }
            }        
        backSquares.push_back(negyzet);
        t=t+360/90;
    }
    for (int i=0;i<backSquares.size();i++){
        squares.push_back(backSquares[i]);
    }
}

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquare();
	glutSwapBuffers();
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		fillSquare(float(xMouse),winHeight-float(yMouse));
	}
		
}

void update(int n)
{   
    if (vectorprinter<vectorsize){
        vectorprinter+=1;
    } 

	glutPostRedisplay();

	glutTimerFunc(5, update, 0);
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
	glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


