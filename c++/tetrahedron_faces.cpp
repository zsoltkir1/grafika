#include <GL/glut.h>
#include <bevgrafmath2017.h>
#include <math.h>

GLsizei winWidth = 800, winHeight = 600;

vec3 tetrahedron[4] = {};

mat4 w2v, rotatedX, scaled, projection;
float alpha = 0;
float pi_180 = pi() / 180;


struct face {
    vec3 p[3];
    vec3 normal;
};

face tetrahedronFaces[4]  = {};

void setNormalVectors(){
    for( int i = 0; i < 4; i++)
        tetrahedronFaces[i].normal = cross (tetrahedronFaces[i].p[1] - tetrahedronFaces[i].p[0], tetrahedronFaces[i].p[2] - tetrahedronFaces[i].p[0]);
}

void initTetrahedron(){
    
    int idx = 0;
    float r = 1;
    float step = 2 * pi() / 3;
    
    for ( float t = 0; idx < 3; t += step){
        
        tetrahedron[idx].x = cos(t) * r;
        tetrahedron[idx].y = sin(t) * r;
        tetrahedron[idx].z = 0.1;
        idx++;
    }
    tetrahedron[3].x = 0; tetrahedron[3].y = 0; tetrahedron[3].z = 2;
    
    tetrahedronFaces[0].p[0] = tetrahedron[0];
    tetrahedronFaces[0].p[1] = tetrahedron[2];
    tetrahedronFaces[0].p[2] = tetrahedron[1];
    
    tetrahedronFaces[1].p[0] = tetrahedron[0];
    tetrahedronFaces[1].p[1] = tetrahedron[1];
    tetrahedronFaces[1].p[2] = tetrahedron[3];
    
    tetrahedronFaces[2].p[0] = tetrahedron[1];
    tetrahedronFaces[2].p[1] = tetrahedron[2];
    tetrahedronFaces[2].p[2] = tetrahedron[3];
    
    tetrahedronFaces[3].p[0] = tetrahedron[2];
    tetrahedronFaces[3].p[1] = tetrahedron[0];
    tetrahedronFaces[3].p[2] = tetrahedron[3];
    
    setNormalVectors();
    
}

void initMatrices(){
    
    scaled = scale ( vec3( 3.0, 3.0, 3.0 ) );
    
    vec2 windowSize = {10, 10};
    vec2 windowPosition = { -5, -5 };
    vec2 viewportSize = { 450, 450};
    vec2 viewportPosition = { winWidth / 2 - viewportSize.x / 2, winHeight / 2 - viewportSize.y / 2 };
    w2v = windowToViewport3(windowPosition, windowSize, viewportPosition, viewportSize);
    
    projection = ortho();
    
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0);
    glLineWidth(1.0);
    
    initTetrahedron();
    initMatrices();
}

void drawFaces(){
    
    glColor3f(0,0,0);
    
    mat4 M = w2v * projection * scaled * rotateX(alpha);
    
    for( int idx = 0; idx < 4; idx++ ){
        
        face f = tetrahedronFaces[idx];
        
        glBegin(GL_LINE_LOOP);
        for ( int i = 0; i < 3; i++ ){
            
            vec4 pointH = ihToH( f.p[i] );
            vec4 transformedPoint = M * pointH;
            
            if(transformedPoint.w != 0){
                vec3 result = hToIh(transformedPoint);
                if(result.z == 0){
                    glVertex2f( result.x, result.y );
                }
            }
            
        }
        glEnd();
   
    }
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 0, 0);
    
    drawFaces();
    
    glutSwapBuffers();
}

void update(int value)
{
    alpha += pi_180;
    if ( alpha >= 2*pi() ) {
        alpha = 0;
    }
    
    glutPostRedisplay();
    
    glutTimerFunc(10, update, 0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetrahedron");
    
    init();
    glutDisplayFunc(display);

    glutTimerFunc(10, update, 0);
    
    
    glutMainLoop();
    return 0;
}




