#include <GL/glut.h>                    // (or others, depending on the system in use)
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <windows.h>

using namespace std;

#define BLACK 0.0,0.0,0.0
#define WHITE 1.0,1.0,1.0
#define GRAY 0.5,0.5,0.5

#define RED 1.0,0.0,0.0
#define DRED 0.5,0.0,0.0
#define GREEN 0.0,1.0,0.0
#define DGREEN 0.0,0.5,0.0
#define BLUE 0.0,0.0,1.0
#define DBLUE 0.0,0.0,0.5

#define YELLOW 1.0,1.0,0.0
#define DYELLOW 0.5,0.5,0.0
#define PURPLE 1.0,0.0,1.0
#define DPURPLE 0.5,0.0,0.5
#define CYAN 0.0,1.0,1.0
#define DCYAN 0.0,0.5,0.5

#define BROWN 102.0/255.0,51.0/255.0,0.0
#define ORANGE 1.0,128.0/255.0,0.0
#define DORANGE 0.5,64.0/255.0,0.0

#define PI M_PI

typedef struct point2d { GLdouble x, y; } POINT2D;
typedef struct point3d { GLdouble x, y, z; } POINT3D;
typedef struct hom2d { GLdouble x1, x2, x3; } HOM2D;
typedef struct hom3d { GLdouble x1, x2, x3, x4; } HOM3D;
typedef struct page { GLint p1, p2, p3, p4; GLint color; } PAGE;
typedef struct polygon {POINT3D *P; int n; } POLYGON;
  

GLsizei winWidth = 800, winHeight = 600;

POINT2D initPoint2D(GLfloat x, GLfloat y) {
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}

POINT3D initPoint3D(GLdouble x, GLdouble y, GLdouble z) {
    POINT3D P;
    P.x = x;
    P.y = y;
    P.z = z;
    return P;
}

HOM3D initHom3D(GLdouble x1, GLdouble x2, GLdouble x3, GLdouble x4) {
    HOM3D P;
    P.x1 = x1;
    P.x2 = x2;
    P.x3 = x3;
    P.x4 = x4;
    return P;
}

PAGE initPage(GLint p1, GLint p2, GLint p3, GLint p4, GLint color) {
    PAGE P;
    P.p1 = p1;
    P.p2 = p2;
    P.p3 = p3;
    P.p4 = p4;
    P.color = color;
    return P;
}

POLYGON initPolygon(POINT3D *P, int n) {
    POLYGON pol;
    pol.P = P;
    pol.n = n;
    return pol;
}

POINT3D toPoint3D(HOM3D a) {
    return initPoint3D(a.x1/a.x4, a.x2/a.x4, a.x3/a.x4);
}

POINT3D toPoint3D(GLdouble *p) {
    return initPoint3D(p[0]/p[3], p[1]/p[3], p[2]/p[3]);
}

HOM3D toHom3D(POINT3D a) {
    return initHom3D(a.x, a.y, a.z, 1);
}

HOM3D toHom3D(GLdouble *p) {
    return initHom3D(p[0], p[1], p[2], p[3]);
}

GLdouble* toArray(POINT3D a) {
    GLdouble* p = new double[4];
    p[0] = a.x;
    p[1] = a.y;
    p[2] = a.z;
    p[3] = 1.0;
    return p;
}

void printCoordinates(POINT3D p) {
    printf("%.2f\t%.2f\t%.2f\n", p.x, p.y, p.z);
}

void printMatrix(GLdouble **M) {
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4; j++) {
            printf("%.2f ", M[i][j]);
        }
        printf("\n");
    }
}

// kockák száma
int number = 7;
POLYGON *cubes = new POLYGON[7];
PAGE *cubePages = new PAGE[21];
// kockalapok száma (ez mindig változik)
GLint pageNum = 0;
// körhenger sugara
GLdouble r = 3;   // 2
// hengeren körben hol helyezkedünk el
GLdouble angle = PI/4;
#define MAXHIGH 10
#define MINHIGH -MAXHIGH
GLdouble high = 2.0;
GLdouble centralS = 0.7;  // 2
POINT3D C = initPoint3D(r*cos(angle), r*sin(angle), high);
POINT3D P = initPoint3D(0,0,0);
POINT3D up = initPoint3D(0,0,1);


void transform(POLYGON pol, GLdouble** M) {
    GLdouble *points;
    for(int p = 0 ; p < pol.n ; p++) {
        points = toArray(pol.P[p]);
        GLdouble tmp[4];
        for(int i = 0 ; i < 4 ; i++) {
            tmp[i] = 0.0;
            for(int j = 0 ; j < 4 ; j++) {
                tmp[i] += M[i][j] * points[j];
            }
        }
        pol.P[p] = toPoint3D(tmp);
    }
    delete points;
}

void initCubes() {
    for(int i = 0 ; i < number ; i++) {
        POINT3D *P = new POINT3D[8];
        P[0] = initPoint3D(0.5, 0.5, -0.5);
        P[1] = initPoint3D(-0.5, 0.5, -0.5);
        P[2] = initPoint3D(-0.5, -0.5, -0.5);
        P[3] = initPoint3D(0.5, -0.5, -0.5);

        P[4] = initPoint3D(0.5, 0.5, 0.5);
        P[5] = initPoint3D(-0.5, 0.5, 0.5);
        P[6] = initPoint3D(-0.5, -0.5, 0.5);
        P[7] = initPoint3D(0.5, -0.5, 0.5);
        switch(i) {
            case 1: for(int j = 0 ; j < 8 ; j++) P[j].x += 2.0; break;
            case 2: for(int j = 0 ; j < 8 ; j++) P[j].x -= 2.0; break;
            case 3: for(int j = 0 ; j < 8 ; j++) P[j].y += 2.0; break;
            case 4: for(int j = 0 ; j < 8 ; j++) P[j].y -= 2.0; break;
            case 5: for(int j = 0 ; j < 8 ; j++) P[j].z += 2.0; break;
            case 6: for(int j = 0 ; j < 8 ; j++) P[j].z -= 2.0; break;
        }
        cubes[i] = initPolygon(P, 8);
    }
}

void setCubes() {
    for(int i = 0 ; i < number ; i++) {
        cubes[i].P[0] = initPoint3D(0.5, 0.5, -0.5);
        cubes[i].P[1] = initPoint3D(-0.5, 0.5, -0.5);
        cubes[i].P[2] = initPoint3D(-0.5, -0.5, -0.5);
        cubes[i].P[3] = initPoint3D(0.5, -0.5, -0.5);

        cubes[i].P[4] = initPoint3D(0.5, 0.5, 0.5);
        cubes[i].P[5] = initPoint3D(-0.5, 0.5, 0.5);
        cubes[i].P[6] = initPoint3D(-0.5, -0.5, 0.5);
        cubes[i].P[7] = initPoint3D(0.5, -0.5, 0.5);
        switch(i) {
            case 1: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].x += 2.0; break;
            case 2: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].x -= 2.0; break;
            case 3: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].y += 2.0; break;
            case 4: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].y -= 2.0; break;
            case 5: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].z += 2.0; break;
            case 6: for(int j = 0 ; j < 8 ; j++) cubes[i].P[j].z -= 2.0; break;
        }
    }
}

GLdouble** mul_matrix(GLdouble** M, GLdouble A[][4]) {
    GLdouble** RET = new double*[4];
    for(int i = 0 ; i < 4 ; i++)
        RET[i] = new double[4];

    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4; j++) {
            RET[i][j] = 0.0;
            for(int k = 0 ; k < 4 ; k++) {
                RET[i][j] += A[i][k] * M[k][j];
            }
        }
    }
    return RET;
}

GLdouble** centralisVetit(GLdouble** M, GLdouble s) {
    GLdouble E[4][4] = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {0.0, 0.0, 0.0, 0.0},
                        {0.0, 0.0, -1.0/s, 1.0}};
    return mul_matrix(M, E);
} 

PAGE defCubePages[6] = {
    initPage(0, 1, 5, 4, 1),
    initPage(4, 5, 6, 7, 1),
    initPage(0, 4, 7, 3, 1),
    initPage(0, 3, 2, 1, 1),
    initPage(7, 6, 2, 3, 1),
    initPage(6, 5, 1, 2, 1),
};

// Window
POINT2D A1 = initPoint2D(-1, -1);   POINT2D A2 = initPoint2D(1, 1);
// Viewport
GLdouble minuss = -100;   // hogy a képernyő közepén legyenek a kockák
POINT2D B1 = initPoint2D(0, minuss); POINT2D B2 = initPoint2D(0+winWidth/1, 0+winWidth/1+minuss);
GLdouble** windowToViewport(GLdouble** M, POINT2D W1, POINT2D W2, POINT2D V1, POINT2D V2) {
    GLdouble _00 = (V2.x - V1.x) / (W2.x - W1.x);
    GLdouble _11 = (V2.y - V1.y) / (W2.y - W1.y);
    GLdouble _03 = V1.x - W1.x * _00;
    GLdouble _13 = V1.y - W1.y * _11;
    GLdouble VW[4][4] = {{_00, 0.0, 0.0, _03},
                        {0.0, _11, 0.0, _13},
                        {0.0, 0.0, 1.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
    return mul_matrix(M, VW);
}

POINT3D subPoints(POINT3D a, POINT3D b) {
    return initPoint3D(b.x-a.x, b.y-a.y, b.z-a.z);
}

// point X point
POINT3D vektorialis(POINT3D a, POINT3D b) {
    return initPoint3D(a.y*b.z - a.z*b.y, 
                       -(a.x*b.z - a.z*b.x),
                       a.x*b.y - a.y*b.x);
}

// CaCb X CaCc
POINT3D vektorialis(PAGE lap) {
    POINT3D a = subPoints(cubes[lap.color].P[lap.p1], cubes[lap.color].P[lap.p2]);
    POINT3D b = subPoints(cubes[lap.color].P[lap.p1], cubes[lap.color].P[lap.p3]);

    return initPoint3D(
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    );
}

GLdouble getNorm(POINT3D v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

POINT3D normalize(POINT3D v) {
    GLdouble n = getNorm(v);
    return initPoint3D(v.x/n, v.y/n, v.z/n);
}

GLdouble skalar(POINT3D a, POINT3D b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

POINT3D addPoints(POINT3D a, POINT3D b) {
    return initPoint3D(a.x+b.x, a.y+b.y, a.z+b.z);
}

GLdouble** K(GLdouble** M, POINT3D u, POINT3D v, POINT3D w) {
    GLdouble K[4][4] = {u.x, u.y, u.z, -skalar(C, u),
                        v.x, v.y, v.z, -skalar(C, v),
                        w.x, w.y, w.z, -skalar(C, w),
                        0, 0, 0, 1};
    return mul_matrix(M, K);
}

GLint keyStates[256];
void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void generatePages() {
    PAGE lap;
    pageNum = 0;
    for(int i = 0 ; i < number ; i++) {
        for(int j = 0 ; j < 6 ; j++) { 
            lap = initPage(defCubePages[j].p1,
                           defCubePages[j].p2,
                           defCubePages[j].p3,
                           defCubePages[j].p4,
                           i);
            if(skalar(vektorialis(lap), subPoints(cubes[i].P[lap.p1], initPoint3D(0, 0, centralS))) >= 0) {
                cubePages[pageNum++] = lap;
            }
        }
    }
    //printf("%d\n", pageNum);
}

POINT3D getLapCenter(PAGE lap) {
    GLdouble x,y,z;
    x = y = z = 0;

    x += cubes[lap.color].P[lap.p1].x;
    x += cubes[lap.color].P[lap.p2].x;
    x += cubes[lap.color].P[lap.p3].x;
    x += cubes[lap.color].P[lap.p4].x;

    y += cubes[lap.color].P[lap.p1].y;
    y += cubes[lap.color].P[lap.p2].y;
    y += cubes[lap.color].P[lap.p3].y;
    y += cubes[lap.color].P[lap.p4].y;

    z += cubes[lap.color].P[lap.p1].z;
    z += cubes[lap.color].P[lap.p2].z;
    z += cubes[lap.color].P[lap.p3].z;
    z += cubes[lap.color].P[lap.p4].z;

    return initPoint3D(x/4, y/4, z/4);

}

GLdouble pointPointDist(POINT3D p1, POINT3D p2) {
    GLdouble t1 = p1.x - p2.x; 
    GLdouble t2 = p1.y - p2.y;
    GLdouble t3 = p1.z - p2.z;
    return sqrt(t1*t1 + t2*t2 + t3*t3);
}

int myCompare(const void *a, const void *b) {
    PAGE _a = *((PAGE*)a);
    PAGE _b = *((PAGE*)b);

    POINT3D tmp = initPoint3D(0,0, centralS);
    if(pointPointDist(getLapCenter(_a), tmp) < pointPointDist(getLapCenter(_b), tmp)) return 1;
    if(pointPointDist(getLapCenter(_a), tmp) == pointPointDist(getLapCenter(_b), tmp)) return 0;
    if(pointPointDist(getLapCenter(_a), tmp) > pointPointDist(getLapCenter(_b), tmp)) return -1;
}

GLdouble** M = new GLdouble*[4];

void generateCubes() {
    setCubes();
    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < 4 ; j++)
            if(i == j)
                M[i][j] = 1.0;
            else 
                M[i][j] = 0.0;
    // z
    //POINT3D w = normalize(addPoints(P, C));
    POINT3D w = normalize(subPoints(C, P));
    w.x *= -1; w.y *= -1; w.z *= -1;
    // x
    POINT3D u = normalize(vektorialis(up, w));
    // y
    POINT3D v = vektorialis(w, u);
    M = K(M, u, v, w);

    for(int i = 0 ; i < number ; i++)
        transform(cubes[i], M);
    generatePages();
    qsort(cubePages, pageNum, sizeof(PAGE), myCompare);

    for(int i = 0 ; i < 4 ; i++)
        for(int j = 0 ; j < 4 ; j++)
            if(i == j)
                M[i][j] = 1.0;
            else 
                M[i][j] = 0.0;
    M = centralisVetit(M, centralS);
    M = windowToViewport(M, A1, A2, B1, B2);
    for(int i = 0 ; i < number ; i++)
        transform(cubes[i], M);
    
}

void init (void)
{
    glClearColor (WHITE, 0.0);	// Set display-window color to white.

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, winWidth, 0.0, winHeight);
    glEnable (GL_POINT_SMOOTH);
    glPointSize(5);
    glLineWidth(3);
    initCubes();
    for(int i = 0 ; i < 4 ; i++)
        M[i] = new GLdouble[4];
    generateCubes();
}


void keyOperateions() {
    //GLdouble delta = 0.0005;  // sleep nélkül
    GLdouble delta = 0.0125;
    bool ok = false;
    if(keyStates['a']) { angle -= delta; C.x = r*cos(angle); C.y = r*sin(angle); ok = true;}
    if(keyStates['d']) { angle += delta; C.x = r*cos(angle); C.y = r*sin(angle); ok = true;}

    if(keyStates['w'] && high < MAXHIGH) { high += delta*5; C.z = high; ok = true;}
    if(keyStates['s'] && high > MINHIGH) { high -= delta*5; C.z = high; ok = true;}

    // 2PI = 0.0 = -2PI
    if(fabs(angle) > 2*PI)
        angle = 0.0;

    if(ok) {
        generateCubes();
    }
    glutPostRedisplay();
}

void drawPage(PAGE lap) {
    switch(lap.color) {
        case 0: glColor3f(RED); break;
        case 1: glColor3f(BLUE); break;
        case 2: glColor3f(GREEN); break;
        case 3: glColor3f(PURPLE); break;
        case 4: glColor3f(YELLOW); break;
        case 5: glColor3f(CYAN); break;
        case 6: glColor3f(ORANGE); break;
    }
    glBegin(GL_POLYGON);
        glVertex2d(cubes[lap.color].P[lap.p1].x, cubes[lap.color].P[lap.p1].y);
        glVertex2d(cubes[lap.color].P[lap.p2].x, cubes[lap.color].P[lap.p2].y);
        glVertex2d(cubes[lap.color].P[lap.p3].x, cubes[lap.color].P[lap.p3].y);
        glVertex2d(cubes[lap.color].P[lap.p4].x, cubes[lap.color].P[lap.p4].y);
    glEnd();

    switch(lap.color) {
        case 0: glColor3f(DRED); break;
        case 1: glColor3f(DBLUE); break;
        case 2: glColor3f(DGREEN); break;
        case 3: glColor3f(DPURPLE); break;
        case 4: glColor3f(DYELLOW); break;
        case 5: glColor3f(DCYAN); break;
        case 6: glColor3f(DORANGE); break;
    }
    glBegin(GL_LINE_LOOP);
        glVertex2d(cubes[lap.color].P[lap.p1].x, cubes[lap.color].P[lap.p1].y);
        glVertex2d(cubes[lap.color].P[lap.p2].x, cubes[lap.color].P[lap.p2].y);
        glVertex2d(cubes[lap.color].P[lap.p3].x, cubes[lap.color].P[lap.p3].y);
        glVertex2d(cubes[lap.color].P[lap.p4].x, cubes[lap.color].P[lap.p4].y);
    glEnd();
}

void draw (void)
{
    keyOperateions();
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.

    for(int i = 0 ; i < pageNum ; i++) {
        drawPage(cubePages[i]);
    }

    glutSwapBuffers();
    Sleep(15);
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (65, 10);   // Set top-left display-window position.
    glutInitWindowSize (winWidth, winHeight);      // Set display-window width and height.
    glutCreateWindow ("An Example OpenGL Program"); // Create display window.

    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (draw);       // Send graphics to display window.
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}