#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

int N = 10;

vec2 starOuter[10] = {  };
vec2 starOuterOriginal[10] = {  };
vec2 starInner[10]= {  };
vec2 starInnerOriginal[10] = {  };

vec2 starCenter = { (float)(winWidth / 2), (float)(winHeight / 2) };

vec2 s = {1, 1};
float scaleChange = 0.025;
float t = 0;

void initStar(){
    
    int idx = 0;
    float R = 100, r = 50;
    
    for ( float T = 0, t = pi() / N; idx < N; T += 2 * pi() / N, t += 2 * pi() / N){
        
        starOuterOriginal[idx].x = starOuter[idx].x = cos(T) * R + starCenter.x;
        starOuterOriginal[idx].y = starOuter[idx].y = sin(T) * R + starCenter.y;
        
        starInnerOriginal[idx].x = starInner[idx].x = cos(t) * r + starCenter.x;
        starInnerOriginal[idx].y = starInner[idx].y = sin(t) * r + starCenter.y;
        
        idx++;
    }
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
}

void drawStar(){
    
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++){
        glVertex2f(starOuter[i].x, starOuter[i].y);
        glVertex2f(starInner[i].x, starInner[i].y);
        
    }
    glEnd();
    
    glBegin(GL_LINES);
    for (int i = 0; i < N; i++){
        glVertex2f(starOuter[i].x, starOuter[i].y);
        glVertex2f(starInner[i].x, starInner[i].y);
        
    }
    glEnd();
    
    glBegin(GL_LINES);
    for (int i = 0; i < N - 1; i++){
        glVertex2f(starOuter[i + 1].x, starOuter[i + 1].y);
        glVertex2f(starInner[i].x, starInner[i].y);
        
    }
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(starOuter[0].x, starOuter[0].y);
    glVertex2f(starInner[N - 1].x, starInner[N - 1].y);
    glEnd();
    
}



void rotateStar(){
    
    mat3 transToO = translate( -1 * starCenter );
    mat3 rotated = rotate( t );
    mat3 scaled = scale ( s );
    mat3 transToC = translate( starCenter );
    mat3 M = transToC * rotated * scaled * transToO;
    
    for ( int i = 0; i < N; i++ ){
        
        vec3 pointH = ihToH( starOuterOriginal[i] );
        vec3 rotatedPointH = M * pointH;
        if(rotatedPointH.z != 0){
            vec2 result = hToIh(rotatedPointH);
            starOuter[i] = { result.x, result.y  };
        }
        
        pointH = ihToH( starInnerOriginal[i] );
        rotatedPointH = M * pointH;
        if(rotatedPointH.z != 0){
            vec2 result = hToIh(rotatedPointH);
            starInner[i] = { result.x, result.y  };
        }
        
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawStar();
    
    glutSwapBuffers();
}

void update(int v){
    
    rotateStar();
    
    t += pi() / 180;
    
    if ( t > 2 * pi() ){
        t = 0;
    }
    
    s += scaleChange;

    if ( s.x > 3 || s.x < 0.25 ){
        scaleChange *= -1;
    }
    
    
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformation");
    
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    
    glutMainLoop();
    return 0;
}




