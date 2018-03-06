#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;

vec2 points[6] = { {100, 100}, {500, 100}, {500, 500}, {100, 500},{250,250},{300,300} };
vec2 asd = {0,0};

GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_STIPPLE);
	glPointSize(8.0);
	glLineWidth(5.0);
	glLineStipple(1, 0xFF00);
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

vec2 a=metszespont(points[0],points[1],points[4],points[5]);
vec2 b=metszespont(points[2],points[3],points[4],points[5]);

void teglalapbanMarad(){
    a= metszespont(points[0],points[1],points[4],points[5]);
    b= metszespont(points[2],points[3],points[4],points[5]);
    if (a.x>points[1].x){
        a= metszespont(points[1],points[2],points[4],points[5]);
    }
    if (a.x<points[0].x){
        a= metszespont(points[3],points[0],points[4],points[5]);
    }
    if (b.x>points[1].x){
        b= metszespont(points[1],points[2],points[4],points[5]);
    }
    if (b.x<points[0].x){
        b= metszespont(points[3],points[0],points[4],points[5]);        
    }
}

void pontokKirajzolas(){
    GLint i,j;
    vec2 egyenes=normalVector(points[4],points[5]);
    vec2 teteje=normalVector(points[2],points[3]);
    vec2 alja=normalVector(points[0],points[1]);
    vec2 jobboldala=normalVector(points[1],points[2]);
    vec2 baloldala=normalVector(points[3],points[0]);
    glColor3f(1.0,1.0,1.0);  
    glBegin(GL_POINTS);
    for (i=0;i<winWidth;i+=24){
        for (j=0;j<winHeight;j+=24){          
            if ((egyenes.x)*i+(egyenes.y)*j>(egyenes.x)*points[4].x+(egyenes.y)*points[4].y){
                glColor3f(0.0,1.0,1.0);  
            }
            if ((egyenes.x)*i+(egyenes.y)*j<(egyenes.x)*points[4].x+(egyenes.y)*points[4].y){
                glColor3f(1.0,0.0,1.0);  
            }
            if ((teteje.x)*i+(teteje.y)*j<(teteje.x)*points[2].x+(teteje.y)*points[2].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((alja.x)*i+(alja.y)*j<(alja.x)*points[0].x+(alja.y)*points[0].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((jobboldala.x)*i+(jobboldala.y)*j<(jobboldala.x)*points[1].x+(jobboldala.y)*points[1].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((baloldala.x)*i+(baloldala.y)*j<(baloldala.x)*points[3].x+(baloldala.y)*points[3].y){
                glColor3f(1.0,1.0,1.0);  
            }
            glVertex2f(i, j);
        }
    }
    for (i=12;i<winWidth;i+=24){
        for (j=12;j<winHeight;j+=24){          
            if ((egyenes.x)*i+(egyenes.y)*j>(egyenes.x)*points[4].x+(egyenes.y)*points[4].y){
                glColor3f(0.0,1.0,1.0);  
            }
            if ((egyenes.x)*i+(egyenes.y)*j<(egyenes.x)*points[4].x+(egyenes.y)*points[4].y){
                glColor3f(1.0,0.0,1.0);  
            }
            if ((teteje.x)*i+(teteje.y)*j<(teteje.x)*points[2].x+(teteje.y)*points[2].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((alja.x)*i+(alja.y)*j<(alja.x)*points[0].x+(alja.y)*points[0].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((jobboldala.x)*i+(jobboldala.y)*j<(jobboldala.x)*points[1].x+(jobboldala.y)*points[1].y){
                glColor3f(1.0,1.0,1.0);  
            }
            if ((baloldala.x)*i+(baloldala.y)*j<(baloldala.x)*points[3].x+(baloldala.y)*points[3].y){
                glColor3f(1.0,1.0,1.0);  
            }
            glVertex2f(i, j);
        }
    }
    glEnd();
}

void display() {
    teglalapbanMarad();

	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);

    pontokKirajzolas();
    /*for (i=points[3].x; i<points[2].x-20; i+=20){
        for (j=points[0].y; j<points[3].y-20; j+=20){
            if(j>300) {
                glColor3f(0.0,1.0,1.0);
            }
            else{
                glColor3f(1.0,1.0,1.0);
            }
            glVertex2f(i+10, j+10);
        }        
    }*/

	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 4; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (i = 0; i < 6; i++)
		glVertex2f(points[i].x, points[i].y);
	glEnd();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
	glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
	glEnd();

    //std::cout<<"reketyebokor"<<std::endl;
    
    std::cout<<a.x<<std::endl;
    std::cout<<a.y<<std::endl;
    std::cout<<b.x<<std::endl;
    std::cout<<b.y<<std::endl;
    
	glutSwapBuffers();
}

GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y) {
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
		if ((i = getActivePoint1(points, 6, 8, xMouse, winHeight - yMouse)) != -1)
			dragged = i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_UP)
		dragged = -1;
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
	GLint i;
	if (dragged >= 4) {
		points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
		glutPostRedisplay();
	}
    if (dragged == 0) {
        points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
        points[1].y = winHeight - yMouse;
        points[3].x = xMouse;
    }
    if (dragged == 1) {
        points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
        points[2].x = xMouse;
        points[0].y = winHeight - yMouse;
    }
    if (dragged == 2) {
        points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
        points[1].x = xMouse;
        points[3].y = winHeight - yMouse;
    }
    if (dragged == 3) {
        points[dragged].x = xMouse;
		points[dragged].y = winHeight - yMouse;
        points[2].y = winHeight - yMouse;
        points[0].x = xMouse;
    }
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
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
    glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


