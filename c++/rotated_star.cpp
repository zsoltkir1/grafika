#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <math.h>
#include <iostream>

GLsizei winWidth = 800, winHeight = 600;

vec2 starOuter[6] = {  };
vec2 starOuterOriginal[6] = {  };
vec2 starInner[6]= {  };
vec2 starInnerOriginal[6] = {  };

vec2 starCenter = { (float)(winWidth / 2), (float)(winHeight / 2) };

mat3 M;
vec2 s = {1, 1};
float scaleChange = 0.0001;
float t = 0;


int rotateCounter = 0;

void initStar(){
    
    int idx = 0;
    float R = 100, r = 50;
    
    for ( float T = 0, t = pi() / 6; idx < 6; T += pi() / 3, t += pi() / 3 ){
        
        starOuterOriginal[idx].x = starOuter[idx].x = cos(T) * R + starCenter.x;
        starOuterOriginal[idx].y = starOuter[idx].y = sin(T) * R + starCenter.y;
        
        starInnerOriginal[idx].x = starInner[idx].x = cos(t) * r + starCenter.x;
        starInnerOriginal[idx].y = starInner[idx].y = sin(t) * r + starCenter.y;
        
        idx++;
    }
}

void rotateStarInit(){
    
    mat3 transToO = translate( -1 * starCenter );
    mat3 rotated = rotate( pi() / 180 );
    mat3 transToC = translate( starCenter );
    M = transToC * rotated * transToO;
	/*mat3 transToO = translate( -1 * starCenter );
    mat3 rotated = rotate( t );
    mat3 scaled = scale ( s );
    mat3 transToC = translate( starCenter );
    mat3 M = transToC * rotated * scaled * transToO;*/
    
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    glLineWidth(1.0);
    
    initStar();
    //rotateStarInit();
}

void drawStar(){
    
    glBegin(GL_POINTS);
    for (int i = 0; i < 6; i++){
        glVertex2f(starOuter[i].x, starOuter[i].y);
        glVertex2f(starInner[i].x, starInner[i].y);
        
    }
    glEnd();
    
    glBegin(GL_LINES);
    for (int i = 0; i < 6; i++){
        glVertex2f(starOuter[i].x, starOuter[i].y);
        glVertex2f(starInner[i].x, starInner[i].y);
        
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++){
        glVertex2f(starOuter[i + 1].x, starOuter[i + 1].y);
        glVertex2f(starInner[i].x, starInner[i].y);

    }
    glEnd();
    
    glBegin(GL_LINES);
        glVertex2f(starOuter[0].x, starOuter[0].y);
        glVertex2f(starInner[5].x, starInner[5].y);
    glEnd();
    
}



void rotateStar(){
    
	mat3 transToO = translate( -1 * starCenter );
    mat3 rotated = rotate( t );
    mat3 scaled = scale ( s );
    mat3 transToC = translate( starCenter );
    mat3 M = transToC * rotated * scaled * transToO;
	
    for ( int i = 0; i < 6; i++ ){
        vec3 pointH = ihToH( starOuter[i] );
        vec3 rotatedPointH = M * pointH;
        if(rotatedPointH.z != 0){
            vec2 result = hToIh(rotatedPointH);
            starOuter[i] = { result.x, result.y  };
        }
        
        pointH = ihToH( starInner[i] );
        rotatedPointH = M * pointH;
        if(rotatedPointH.z != 0){
            vec2 result = hToIh(rotatedPointH);
            starInner[i] = { result.x, result.y  };
        }

    }
    
    rotateCounter++;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawStar();

    glutSwapBuffers();
}

void update(int v){
    
    rotateStar();
    
    /*if ( rotateCounter > 360 ){
        for (int i = 0; i < 6; i++){
            starOuter[i] = starOuterOriginal[i];
            starInner[i] = starInnerOriginal[i];
        }
        
        rotateCounter = 0;
    }*/
	
	t += pi() / 180;
    
    if ( t > 2 * pi() ){
        t = 0;
    }
    
    s += scaleChange;
	
	std::cout<<s.x<<std::endl;
    if ( s.x > 1.01 || s.x < 0.99 ){
		std::cout<<s.x<<std::endl;
        scaleChange *= -1;
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformation");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(500, update, 0);

    glutMainLoop();
    return 0;
}




