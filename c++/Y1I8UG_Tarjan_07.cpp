#include <GL/glut.h>
#include <bevgrafmath2017.h>

int winWidth=700,winHeight=600;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void tengely(mat3 w2v,float tartomanyeleje,float tartomanyvege){
    vec3 frame[4]={{tartomanyeleje,tartomanyeleje,1},{tartomanyvege,tartomanyeleje,1},{tartomanyvege,tartomanyvege,1},{tartomanyeleje,tartomanyvege,1}};
    for (int i=0;i<4;i++) frame[i]=w2v*frame[i];
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    for (int i=0;i<4;i++) glVertex2f(frame[i].x,frame[i].y);    
    glEnd();
    vec3 xtengely1={tartomanyeleje,0,1};
    vec3 xtengely2={tartomanyvege,0,1};
    vec3 ytengely1={0,tartomanyeleje,1};
    vec3 ytengely2={0,tartomanyvege,1};
    vec3 xtw1=w2v*xtengely1;
    vec3 xtw2=w2v*xtengely2;
    vec3 ytw1=w2v*ytengely1;
    vec3 ytw2=w2v*ytengely2;
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_LINES);
    glVertex2f(xtw1.x,xtw1.y);
    glVertex2f(xtw2.x,xtw2.y);
    glVertex2f(ytw1.x,ytw1.y);
    glVertex2f(ytw2.x,ytw2.y);
    glEnd();
}

void fuggveny1(){
	mat3 w2v=windowToViewport2(vec2(-1,-1), vec2(2,2), vec2(10,winHeight-10-280), vec2(280,280));  	
    tengely(w2v,-1,1);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
	for (float i=-1;i<=1;i=i+0.01f){
		vec3 p={i,pow(i,3.0f),1};
		p=w2v*p;
		glVertex2f(p.x, p.y);    
	}  
    glEnd();
}

void fuggveny2(){
	mat3 w2v=windowToViewport2(vec2(-5,-5), vec2(10,10), vec2(410,winHeight-10-280), vec2(280,280));
	tengely(w2v,-5,5);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.6, 0.0);
	for (float i=-5;i<=0;i=i+0.001f){
		vec3 p={i,1/i,1};
		if ((i!=0) and (p.y>=-5)){
            p=w2v*p;
            glVertex2f(p.x, p.y);
        }         
	}  
    glEnd();
    glBegin(GL_LINE_STRIP);
    for (float i=0;i<=5;i=i+0.001f){
        if (i==0) continue;
		vec3 p={i,1/i,1};
        if ((i!=0) and (p.y<=5)){
            p=w2v*p;
            glVertex2f(p.x, p.y);
        }     
		     
	}  
    glEnd();
}

void fuggveny3(){
	mat3 w2v=windowToViewport2(vec2(-2*pi(),-2*pi()), vec2(4*pi(),4*pi()), vec2(10,winHeight-10-280-300), vec2(280,280));
	tengely(w2v,-2*pi(),2*pi());
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 1.0, 0.0);
	for (float i=-2*pi();i<=2*pi();i=i+0.01f){
		vec3 p={i,sin(i),1};
		p=w2v*p;
		glVertex2f(p.x, p.y);    
	}  
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 1.0);
	for (float i=-2*pi();i<=2*pi();i=i+0.01f){
		vec3 p={i,cos(i),1};
		p=w2v*p;
		glVertex2f(p.x, p.y);    
	}  
    glEnd();
}

void fuggveny4(){
	mat3 w2v=windowToViewport2(vec2(-4*pi(),-4*pi()), vec2(8*pi(),8*pi()), vec2(410,winHeight-10-280-300), vec2(280,280));
	tengely(w2v,-4*pi(),4*pi());
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 1.0);
	for (float i=-1.5*pi();i<=2.5*pi();i=i+0.01f){
		vec3 p={i-1.6f*cos(24*i),i-1.6f*sin(25*i),1};
		p=w2v*p;
		glVertex2f(p.x, p.y);    
	}  
    glEnd();
}

void display() {
	GLint i;
	glClear(GL_COLOR_BUFFER_BIT);
    fuggveny1();	
    fuggveny2();
    fuggveny3();
    fuggveny4(); 
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("multiple key press");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}


