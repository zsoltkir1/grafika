#include "GL/glut.h"
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>
#include <time.h>
#include <vector>

GLsizei winWidth = 800, winHeight = 600;
std::vector<vec2> cannonballs1;
std::vector<vec2> cannonballs2;
std::vector<vec2> cannonballdirection;

vec2 irany;
vec2 O;
float r=20,kisr=30,nagyr=80;
int mx,my;

GLint dragged = -1;

GLint Round(GLfloat n) { return (GLint)(n + 0.5); }

void initPoints(){
    cannonballs1.empty();
    
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
	//glEnable(GL_LINE_STIPPLE);
	glPointSize(10.0);
    glLineWidth(3.0);
    initPoints();
	//glLineStipple(1, 0xFF00);
    srand (time(NULL));
    O={200,500};
    irany={5,0};
}

void tar(){
    glColor3f(0.0, 0.1, 0.0);
    glBegin(GL_POINTS);
    if (cannonballs1.size()>0){        
        for (int i=0; i<=cannonballs1.size()-1; i++){   
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

void elipsisSemiCircle(vec2 O, float r) {
	
    glLineWidth(3.0);
    
	glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
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
    glColor3f(0.0, 1.0, 0.0);
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

/*vec2 metszespont(vec2 point1, vec2 point2, vec2 point3, vec2 point4){
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
}*/

void updatefire(){
    if (cannonballs2.size()>0){
        glColor3f(0.0, 1.0, 0.0);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        for (int i=0;i<=cannonballs2.size()-1;i++){
            cannonballs2[i]+=cannonballdirection[i]*5;
            glVertex2d(cannonballs2[i].x,cannonballs2[i].y);
            std::cout<<cannonballs2[i].x<<std::endl;
            std::cout<<cannonballs2[i].y<<std::endl;
        }
        glEnd();
    }
}

void display() {
    //teglalapbanMarad();

	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
    
    agyu();
    
    lovegtorony();
    
    tar();
    
    updatefire();

    /*pontokKirajzolas();

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
	glEnd();*/
    
    glColor3f(0.0f, 0.4f, 0.2f);
	
	elipsisSemiCircle(O, r);

    //std::cout<<"reketyebokor"<<std::endl;
    
    /*std::cout<<a.x<<std::endl;
    std::cout<<a.y<<std::endl;
    std::cout<<b.x<<std::endl;
    std::cout<<b.y<<std::endl;*/
    
	glutSwapBuffers();
}

/*GLint getActivePoint1(vec2 p[], GLint size, GLint sens, GLint x, GLint y) {
	GLint i, s = sens * sens;
	vec2 P = { (float)x, (float)y };

	for (i = 0; i < size; i++)
		if (dist(p[i], P) < s)
			return i;
	return -1;
}
*/

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
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && cannonballs1.size()>=1){
        cannonballs1.pop_back();
        fire();
    }  
}

void processMouse2(GLint xMouse, GLint yMouse) {
	mx=xMouse;
    my=yMouse;
}

/*void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
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
}*/

void bounce(){
    if (O.x<=nagyr) irany.x=irany.x*-1;
    if (O.x>=winWidth-nagyr) irany.x=irany.x*-1;
}

void update(int n)
{
    O+=irany;
    
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
	//glutMotionFunc(processMouseActiveMotion);
    glutTimerFunc(5, update, 0);
	glutMainLoop();
	return 0;
}


