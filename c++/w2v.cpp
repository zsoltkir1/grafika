#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

vec2 points[4] = { {0.5, 0.5}, {-0.5, 0.5}, {-0.5, -0.5}, {0.5, -0.5} };

vec2 windowSize = {2, 2};
vec2 windowPosition = { -1, -1 };

vec2 viewportSize = { 400, 400};
vec2 viewportPosition = { winWidth / 2 - viewportSize.x / 2, winHeight / 2 - viewportSize.y / 2 };

mat3 wTv;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    glLineWidth(1.0);

    wTv = windowToViewport2(windowPosition, windowSize, viewportPosition, viewportSize);


}

void drawViewport(){
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINE_LOOP);
    
    glVertex2f(viewportPosition.x, viewportPosition.y); // left bottom
    glVertex2f(viewportPosition.x + viewportSize.x, viewportPosition.y); // right bottom
    
    glVertex2f(viewportPosition.x + viewportSize.x, viewportPosition.y + viewportSize.y); // right top
    glVertex2f(viewportPosition.x, viewportPosition.y + viewportSize.y); // left top
    
    glEnd();
}

void drawSquare(){
    
    glColor3f(0, 0, 1);
    
    glBegin(GL_LINE_LOOP);
    for( int i = 0; i < 4; i++ ){
        vec3 pH = ihToH( points[i] );
        vec3 resultH = wTv * pH;
        if( resultH.z != 0) {
            vec2 result = hToIh(resultH);
            glVertex2f(result.x, result.y);
        }
    }
    glEnd();
    
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawViewport();
    drawSquare();
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Window 2 Viewport");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}





