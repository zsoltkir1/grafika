#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>
#include <time.h>

GLsizei winWidth = 800, winHeight = 600;

vec2 points[6] = { {100, 100}, {500, 100}, {500, 500}, {100, 500},{250,250},{300,300} };
vec2 irany;
vec2 O;
float r=20;

GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(6.0);
    glLineWidth(3.0);
    srand (time(NULL));
    O={300,200};
    irany={float(rand() % 9 - 4)-0.5f,float(rand() % 9 - 4)-0.5f};
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
    //if (deteredeti!=0){
        vec2 a;
        a.x=detfelcserelt1/deteredeti;
        a.y=detfelcserelt2/deteredeti;
        return a;
    //}
    //else {
    //    vec2 a={-500,-500};
    //    return a;
    //}
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
            float korben = (i-O.x)*(i-O.x)+(j-O.y)*(j-O.y)-r*r;
            if (korben<0) glColor3f(0.0,0.3,0.3);
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
            float korben = (i-O.x)*(i-O.x)+(j-O.y)*(j-O.y)-r*r;
            if (korben<0) glColor3f(0.0,0.3,0.3);
            glVertex2f(i, j);
        }
    }
    glEnd();
}

void bounce(){
    vec2 alsoegyenes=normalVector(points[0],points[1]);
    float const1=alsoegyenes.x*points[0].x+alsoegyenes.y*points[0].y;
    float dist01=fabs(alsoegyenes.x*(-O.x)+alsoegyenes.y*(-O.y)+const1)/sqrt(alsoegyenes.x*alsoegyenes.x+alsoegyenes.y*alsoegyenes.y);
    if (dist01<r){
		irany=-irany+2*(dot(alsoegyenes,irany)/length2(alsoegyenes))*alsoegyenes;
		irany=-irany;
	}
    vec2 felsoegyenes=normalVector(points[2],points[3]);
    float const2=felsoegyenes.x*points[2].x+felsoegyenes.y*points[2].y;
    float dist02=fabs(felsoegyenes.x*(-O.x)+felsoegyenes.y*(-O.y)+const2)/sqrt(felsoegyenes.x*felsoegyenes.x+felsoegyenes.y*felsoegyenes.y);
    if (dist02<r){
		irany=-irany+2*(dot(felsoegyenes,irany)/length2(felsoegyenes))*felsoegyenes;
		irany=-irany;
	}
    vec2 jobbegyenes=normalVector(points[1],points[2]);
    float const3=jobbegyenes.x*points[1].x+jobbegyenes.y*points[1].y;
    float dist03=fabs(jobbegyenes.x*(-O.x)+jobbegyenes.y*(-O.y)+const3)/sqrt(jobbegyenes.x*jobbegyenes.x+jobbegyenes.y*jobbegyenes.y);
    if (dist03<r){
		irany=-irany+2*(dot(jobbegyenes,irany)/length2(jobbegyenes))*jobbegyenes;
		irany=-irany;
	}
    vec2 balegyenes=normalVector(points[3],points[0]);
    float const4=balegyenes.x*points[3].x+balegyenes.y*points[3].y;
    float dist04=fabs(balegyenes.x*(-O.x)+balegyenes.y*(-O.y)+const4)/sqrt(balegyenes.x*balegyenes.x+balegyenes.y*balegyenes.y);
    if (dist04<r){
		irany=-irany+2*(dot(balegyenes,irany)/length2(balegyenes))*balegyenes;
		irany=-irany;
	}
	vec2 kozepsoegyenes=normalVector(points[4],points[5]);
    float const5=kozepsoegyenes.x*points[4].x+kozepsoegyenes.y*points[4].y;	
    float dist05=fabs(kozepsoegyenes.x*(-O.x)+kozepsoegyenes.y*(-O.y)+const5)/sqrt(kozepsoegyenes.x*kozepsoegyenes.x+kozepsoegyenes.y*kozepsoegyenes.y);
    if (dist05<r){
		irany=-irany+2*(dot(kozepsoegyenes,irany)/length2(kozepsoegyenes))*kozepsoegyenes;
		irany=-irany;
	}
}

void display() {
    teglalapbanMarad();

	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);

    pontokKirajzolas();

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
	glVertex2f(points[0].x, points[0].y);
	glVertex2f(points[2].x, points[2].y);
	glVertex2f(points[4].x, points[4].y);
	glVertex2f(points[5].x, points[5].y);
	glEnd();
    
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
	glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
	glEnd();
    
    glColor3f(0.0f, 0.4f, 0.2f);
	
	circle(O, r);
    
	glutSwapBuffers();
}

GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	//for (i = 0; i < size; i++)
		if (dist(p[0], P) < s)
			return 0;
		if (dist(p[2], P) < s)
			return 2;
		if (dist(p[4], P) < s)
			return 4;
		if (dist(p[5], P) < s)
			return 5;
	return -1;
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
	GLint i;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		if ((i = getActivePoint1(points, 6, 3, xMouse, winHeight - yMouse)) != -1)
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
    
    bounce();
	
	O+=irany;
    
	glutPostRedisplay();

	glutTimerFunc(30, update, 0);
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


