#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 800;

int N = 8;
vec3 cube[8] = { };
vec2 drawableCube[8] = {};

mat4 w2v, projection;
float alpha = 0;
float beta = 0;


void initMatrices(){

	projection = ;
    
    vec2 windowSize = { , };
    vec2 windowPosition = { ,  };
    vec2 viewportSize = { , };
    vec2 viewportPosition = { , };
    w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    glLineWidth(1.0);
    
    initMatrices();
}

void drawCube(){
    
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++){
		
    }
    glEnd();

	glBegin(GL_LINES);

	glEnd();
    
}

void transform(){
	mat4 rotation = ;
    mat4 M = w2v * projection * rotation;

    for ( int i = 0; i < N; i++ ){
        
		vec4 pointH = ;
		vec4 transformedPoint = ;

		if (transformedPoint.w != 0) 
		{
			drawableCube[i] = {  };
		}
        
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawCube();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'w':
	
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pyramid");
    
    init();
    glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}




