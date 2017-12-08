#include <GL/glut.h>                    // (or others, depending on the system in use)
#include <iostream>
#include <stdio.h>
#include <cmath>

#define BLACK 0.0,0.0,0.0
#define RED 1.0,0.0,0.0
#define GREEN 0.0,1.0,0.0
#define BLUE 0.0,0.0,1.0
#define ORANGE 1.0,140.0/255.0,0.0
#define PI 3.141592653589793

typedef struct point2d { GLdouble x, y; } POINT2D;
typedef struct point3d { GLdouble x, y, z; } POINT3D;
typedef struct hom2d { GLdouble x1, x2, x3; } HOM2D;
typedef struct hom3d { GLdouble x1, x2, x3, x4; } HOM3D;
typedef struct polygon { POINT3D *P; int n; } POLYGON;

GLsizei winWidth = 800, winHeight = 600;

POINT2D initPoint2D(GLdouble x, GLdouble y) {
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

GLdouble** forgatx(GLdouble** M, GLdouble alfa) {
    GLdouble Fx[4][4] = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, cos(alfa), -sin(alfa), 0.0},
                        {0.0, sin(alfa), cos(alfa), 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
    return mul_matrix(M, Fx);
}

GLdouble** forgaty(GLdouble** M, GLdouble alfa) {
    GLdouble Fy[4][4] = {{cos(alfa), 0.0, sin(alfa), 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {-sin(alfa), 0.0, cos(alfa), 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
    return mul_matrix(M, Fy);
}

GLdouble** forgatz(GLdouble** M, GLdouble alfa) {
    GLdouble Fz[4][4] = {{cos(alfa), -sin(alfa), 0.0, 0.0},
                        {sin(alfa), cos(alfa), 0.0, 0.0},
                        {0.0, 0.0, 1.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
    return mul_matrix(M, Fz);
}

GLdouble** merolegesVetit(GLdouble** M) {
    GLdouble E[4][4] = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {0.0, 0.0, 0.0, 0.0},
                        {0.0, 0.0, 0.0, 1.0}};
    return mul_matrix(M, E);
} 

GLdouble** centralisVetit(GLdouble** M, GLdouble s) {
    GLdouble E[4][4] = {{1.0, 0.0, 0.0, 0.0},
                        {0.0, 1.0, 0.0, 0.0},
                        {0.0, 0.0, 0.0, 0.0},
                        {0.0, 0.0, -1.0/s, 1.0}};
    return mul_matrix(M, E);
} 

// egységkocka
POINT2D A1 = initPoint2D(-1, -1);   POINT2D A2 = initPoint2D(1, 1);
// jobb oldali
POINT2D B1 = initPoint2D(100+300, 100); POINT2D B2 = initPoint2D(winWidth/2+300, winWidth/2);
// bal oldali
POINT2D C1 = initPoint2D(100, 100); POINT2D C2 = initPoint2D(winWidth/2, winWidth/2);
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

GLint keyStates[256];
void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void printMatrix(GLdouble** M) {
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPoints(POLYGON P) {
    for(int i = 0 ; i < P.n ; i++) {
        printf("(%.0f\t%.0f\t%.0f)\n", P.P[i].x, P.P[i].y, P.P[i].z);
    }
    printf("\n");
}

POLYGON* cube1 = new POLYGON[3];
POLYGON* cube2 = new POLYGON[3];

// M1[0] - első kocka, legaljának a mátrixa
GLdouble*** M1 = new GLdouble**[3];
GLdouble*** M2 = new GLdouble**[3];

void initCubes() {
    //std::cout << __func__ << std::endl;
    GLdouble x, y;
    POINT3D* P;
    for(int i = 0 ; i < 3 ; i++) {
        switch(i) {
            case 0:
                x = -0.5; y = -1.0/6.0; break;
            case 1:
                x = -1.0/6.0; y = 1.0/6.0; break;
            case 2:
                x = 1.0/6.0; y = 0.5; break;
        }
        POINT3D *P = new POINT3D[8];
        P[0] = initPoint3D(0.5, 0.5, x);
        P[1] = initPoint3D(-0.5, 0.5, x);
        P[2] = initPoint3D(-0.5, -0.5, x);
        P[3] = initPoint3D(0.5, -0.5, x);

        P[4] = initPoint3D(0.5, 0.5, y);
        P[5] = initPoint3D(-0.5, 0.5, y);
        P[6] = initPoint3D(-0.5, -0.5, y);
        P[7] = initPoint3D(0.5, -0.5, y);

        cube1[i] = initPolygon(P, 8);

        P = new POINT3D[8];
        P[0] = initPoint3D(0.5, 0.5, x);
        P[1] = initPoint3D(-0.5, 0.5, x);
        P[2] = initPoint3D(-0.5, -0.5, x);
        P[3] = initPoint3D(0.5, -0.5, x);

        P[4] = initPoint3D(0.5, 0.5, y);
        P[5] = initPoint3D(-0.5, 0.5, y);
        P[6] = initPoint3D(-0.5, -0.5, y);
        P[7] = initPoint3D(0.5, -0.5, y);
        cube2[i] = initPolygon(P, 8);
    }
    //delete P;
}

void setCubes() {
	GLdouble x, y;
    for(int i = 0 ; i < 3 ; i++) {
        switch(i) {
            case 0:
                x = -0.5; y = -1.0/6.0; break;
            case 1:
                x = -1.0/6.0; y = 1.0/6.0; break;
            case 2:
                x = 1.0/6.0; y = 0.5; break;
        }
        cube1[i].P[0] = initPoint3D(0.5, 0.5, x);
        cube1[i].P[1] = initPoint3D(-0.5, 0.5, x);
        cube1[i].P[2] = initPoint3D(-0.5, -0.5, x);
        cube1[i].P[3] = initPoint3D(0.5, -0.5, x);

        cube1[i].P[4] = initPoint3D(0.5, 0.5, y);
        cube1[i].P[5] = initPoint3D(-0.5, 0.5, y);
        cube1[i].P[6] = initPoint3D(-0.5, -0.5, y);
        cube1[i].P[7] = initPoint3D(0.5, -0.5, y);

        cube2[i].P[0] = initPoint3D(0.5, 0.5, x);
        cube2[i].P[1] = initPoint3D(-0.5, 0.5, x);
        cube2[i].P[2] = initPoint3D(-0.5, -0.5, x);
        cube2[i].P[3] = initPoint3D(0.5, -0.5, x);

        cube2[i].P[4] = initPoint3D(0.5, 0.5, y);
        cube2[i].P[5] = initPoint3D(-0.5, 0.5, y);
        cube2[i].P[6] = initPoint3D(-0.5, -0.5, y);
        cube2[i].P[7] = initPoint3D(0.5, -0.5, y);
    }
    //delete P;
}

void initMs() {
    std::cout << __func__ << std::endl;
    // első kocka mátrixai
    for(int i = 0 ; i < 3 ; i++) {
        M1[i] = new GLdouble*[4];
        for(int j = 0 ; j < 4 ; j++)
            M1[i][j] = new GLdouble[4];
    }
    // második kocka mátrixai
    for(int i = 0 ; i < 3 ; i++) {
        M2[i] = new GLdouble*[4];
        for(int j = 0 ; j < 4 ; j++)
            M2[i][j] = new GLdouble[4];
    }
}

GLdouble ym[3] = {0,0,0};
void setMs() {
    GLdouble rotx2 = M_PI/12;     // "bebillenteni" kicsit előre
    GLdouble rotx1 = M_PI/2;      // elforgatni 90fokkal 
    GLdouble roty = M_PI/3;
	for(int k = 0 ; k < 3 ; k++) {
		for(int i = 0 ; i < 4 ; i++) {
			for(int j = 0 ; j < 4 ; j++) {
				if(i == j)
					M1[k][i][j] = M2[k][i][j] = 1.0;
				else
					M1[k][i][j] = M2[k][i][j] = 0.0;
			}
		}
		

        // visszadönteni x-re nem szabad z-vel
        M1[k] = forgatx(M1[k], rotx1);
        M1[k] = forgaty(M1[k], roty+ym[k]);
        M1[k] = forgatx(M1[k], rotx2);
		M1[k] = centralisVetit(M1[k], 3);
		M1[k] = windowToViewport(M1[k], A1, A2, B1, B2);
		transform(cube1[k], M1[k]);

        M2[k] = forgatx(M2[k], rotx1);
        M2[k] = forgaty(M2[k], roty+ym[k]);
		M2[k] = forgatx(M2[k], rotx2);
        M2[k] = merolegesVetit(M2[k]);
		M2[k] = windowToViewport(M2[k], A1, A2, C1, C2);
		transform(cube2[k], M2[k]);
	}
}

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.

    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, winWidth, 0.0, winHeight);
    glEnable (GL_POINT_SMOOTH);
    glPointSize(5);
    glLineWidth(1.0);

    initCubes();
    initMs();
    setMs();
}

int c = -1;
void keyOperations() {
    bool ok = false;
	GLdouble delta = 0.0005;
	if(keyStates['q']) {
        ok = true;
		ym[0]-=delta;
	}
	if(keyStates['e']) {
        ok = true;
		ym[0]+=delta;
	}
	if(keyStates['a']) {
        ok = true;
		ym[1]-=delta;
	}
	if(keyStates['d']) {
        ok = true;
		ym[1]+=delta;
	}
	if(keyStates['y']) {
        ok = true;
		ym[2]-=delta;
	}
	if(keyStates['c']) {
        ok = true;
		ym[2]+=delta;
	}
    if(ok) {
        setCubes();
        setMs();    
    }
    glutPostRedisplay();
}

void drawCube(POLYGON* cube) {
    glColor3f(BLACK);
    for(int q = 0 ; q < 3 ; q++) {  // cube 1-2-3
        glBegin(GL_LINE_LOOP);
            for(int i = 0 ; i < 4 ; i++){
                glVertex2d(cube[q].P[i].x, cube[q].P[i].y);
            }
        glEnd();
        glBegin(GL_LINE_LOOP);
            for(int i = 4 ; i < 8 ; i++)
                glVertex2d(cube[q].P[i].x, cube[q].P[i].y);
        glEnd();
        glBegin(GL_LINES);
            glVertex2d(cube[q].P[0].x, cube[q].P[0].y);
            glVertex2d(cube[q].P[4].x, cube[q].P[4].y);

            glVertex2d(cube[q].P[1].x, cube[q].P[1].y);
            glVertex2d(cube[q].P[5].x, cube[q].P[5].y);

            glVertex2d(cube[q].P[2].x, cube[q].P[2].y);
            glVertex2d(cube[q].P[6].x, cube[q].P[6].y);

            glVertex2d(cube[q].P[3].x, cube[q].P[3].y);
            glVertex2d(cube[q].P[7].x, cube[q].P[7].y);
        glEnd();
    }
}

void draw (void)
{
    keyOperations();
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
    
    drawCube(cube1);
    drawCube(cube2);

    glutSwapBuffers();
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (65, 10);   // Set top-left display-window position.
    glutInitWindowSize (winWidth, winHeight);      // Set display-window width and height.
    glutCreateWindow ("Lorem ipsum...."); // Create display window.

    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (draw);       // Send graphics to display window.
    glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}