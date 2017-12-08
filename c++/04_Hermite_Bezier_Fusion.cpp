#include <GL/glut.h>                    // (or others, depending on the system in use)
#include <stdio.h>
#include <string>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#define BLACK 0.0,0.0,0.0
#define WHITE 1.0,1.0,1.0
#define RED 1.0,0.0,0.0
#define GREEN 0.0,1.0,0.0
#define BLUE 0.0,0.0,1.0

#define YELLOW 1.0,1.0,0.0
#define CYAN 0.0,1.0,1.0
#define PURPLE 1.0,0.0,1.0
#define PI 3.141592653589793

/***************************************/
double det33(double M[3][3]) {
    return M[0][0] * M[1][1] * M[2][2] +
           M[0][1] * M[1][2] * M[2][0] +
           M[0][2] * M[1][0] * M[2][1] -
           M[2][0] * M[1][1] * M[0][2] -
           M[2][1] * M[1][2] * M[0][0] -
           M[2][2] * M[1][0] * M[0][1];
}

double det44(double** M4) {
    double M41[3][3] = {{M4[1][1], M4[1][2], M4[1][3]},
                        {M4[2][1], M4[2][2], M4[2][3]},
                        {M4[3][1], M4[3][2], M4[3][3]}};

    double M42[3][3] = {M4[1][0], M4[1][2], M4[1][3],
                        M4[2][0], M4[2][2], M4[2][3],
                        M4[3][0], M4[3][2], M4[3][3]};

    double M43[3][3] = {M4[1][0], M4[1][1], M4[1][3],
                        M4[2][0], M4[2][1], M4[2][3],
                        M4[3][0], M4[3][1], M4[3][3]};

    double M44[3][3] = {M4[1][0], M4[1][1], M4[1][2],
                        M4[2][0], M4[2][1], M4[2][2],
                        M4[3][0], M4[3][1], M4[3][2]};

    return M4[0][0] * det33(M41) - M4[0][1] * det33(M42) + M4[0][2] * det33(M43) - M4[0][3] * det33(M44);
}

GLdouble** invert44(GLdouble** M) {
    double** R = new double*[4];
    for(int i = 0 ; i < 4 ; i++)
        R[i] = new double[4];

    // M00 - első indexben sehol sincs 0
    //     - második indexben sehol sincs 0
    // ----------------------- 1. sor ------------------------- //
    double M00[3][3] = {M[1][1], M[1][2], M[1][3],
                        M[2][1], M[2][2], M[2][3],
                        M[3][1], M[3][2], M[3][3]};

    double M01[3][3] = {M[1][0], M[1][2], M[1][3],
                        M[2][0], M[2][2], M[2][3],
                        M[3][0], M[3][2], M[3][3]};

    double M02[3][3] = {M[1][0], M[1][1], M[1][3],
                        M[2][0], M[2][1], M[2][3],
                        M[3][0], M[3][1], M[3][3]};

    double M03[3][3] = {M[1][0], M[1][1], M[1][2],
                        M[2][0], M[2][1], M[2][2],
                        M[3][0], M[3][1], M[3][2]};
    // -------------------------------------------------------- //
    // ----------------------- 2. sor ------------------------- //
    double M10[3][3] = {M[0][1], M[0][2], M[0][3],
                        M[2][1], M[2][2], M[2][3],
                        M[3][1], M[3][2], M[3][3]};

    double M11[3][3] = {M[0][0], M[0][2], M[0][3],
                        M[2][0], M[2][2], M[2][3],
                        M[3][0], M[3][2], M[3][3]};

    double M12[3][3] = {M[0][0], M[0][1], M[0][3],
                        M[2][0], M[2][1], M[2][3],
                        M[3][0], M[3][1], M[3][3]};

    double M13[3][3] = {M[0][0], M[0][1], M[0][2],
                        M[2][0], M[2][1], M[2][2],
                        M[3][0], M[3][1], M[3][2]};
    // -------------------------------------------------------- //
    // ----------------------- 3. sor ------------------------- //
    double M20[3][3] = {M[0][1], M[0][2], M[0][3],
                        M[1][1], M[1][2], M[1][3],
                        M[3][1], M[3][2], M[3][3]};

    double M21[3][3] = {M[0][0], M[0][2], M[0][3],
                        M[1][0], M[1][2], M[1][3],
                        M[3][0], M[3][2], M[3][3]};

    double M22[3][3] = {M[0][0], M[0][1], M[0][3],
                        M[1][0], M[1][1], M[1][3],
                        M[3][0], M[3][1], M[3][3]};

    double M23[3][3] = {M[0][0], M[0][1], M[0][2],
                        M[1][0], M[1][1], M[1][2],
                        M[3][0], M[3][1], M[3][2]};
    // -------------------------------------------------------- //
    // ----------------------- 4. sor ------------------------- //
    double M30[3][3] = {M[0][1], M[0][2], M[0][3],
                        M[1][1], M[1][2], M[1][3],
                        M[2][1], M[2][2], M[2][3]};

    double M31[3][3] = {M[0][0], M[0][2], M[0][3],
                        M[1][0], M[1][2], M[1][3],
                        M[2][0], M[2][2], M[2][3]};

    double M32[3][3] = {M[0][0], M[0][1], M[0][3],
                        M[1][0], M[1][1], M[1][3],
                        M[2][0], M[2][1], M[2][3]};

    double M33[3][3] = {M[0][0], M[0][1], M[0][2],
                        M[1][0], M[1][1], M[1][2],
                        M[2][0], M[2][1], M[2][2]};
    // -------------------------------------------------------- //
    
    R[0][0] = det33(M00);
    R[0][1] = -det33(M10);
    R[0][2] = det33(M20);
    R[0][3] = -det33(M30);

    R[1][0] = -det33(M01);
    R[1][1] = det33(M11);
    R[1][2] = -det33(M21);
    R[1][3] = det33(M31);

    R[2][0] = det33(M02);
    R[2][1] = -det33(M12);
    R[2][2] = det33(M22);
    R[2][3] = -det33(M32);

    R[3][0] = -det33(M03);
    R[3][1] = det33(M13);
    R[3][2] = -det33(M23);
    R[3][3] = det33(M33);

    double det4 = det44(M);

    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            R[i][j] /= det4;
        }
    }

    return R;
}

void printMatrix(GLdouble** M) {
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            printf("%.3f ", M[i][j]);
        }
        printf("\n");
    }
}
/**************************************/

typedef struct point2d { GLdouble x, y; } POINT2D;

GLsizei winWidth = 800, winHeight = 600;
GLint dragged;
int n = 4;
int m = 6;
GLdouble _t[4] = {-2.0, 0.3, 1.5, 1.5};  // paraméterek
POINT2D *H = new POINT2D[n];
POINT2D *B = new POINT2D[m];
GLdouble** G = new double*[2];
GLdouble** M = new GLdouble*[4];
GLdouble** C = new GLdouble*[2];
GLint minus = 0;

POINT2D initPoint2D(GLdouble x, GLdouble y) {
    POINT2D P;
    P.x = x;
    P.y = y;
    return P;
}

GLint keyStates[256];
void keyPressed(unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

GLdouble* pointParameters(GLdouble t) {
    GLdouble* ret = new GLdouble[4];
    ret[0] = t*t*t;
    ret[1] = t*t;
    ret[2] = t;
    ret[3] = 1.0;
    return ret;
}

GLdouble* vectorParameters(GLdouble t) {
    GLdouble* ret = new GLdouble[4];
    ret[0] = 3*t*t;
    ret[1] = 2*t;
    ret[2] = 1.0;
    ret[3] = 0.0;
    return ret;
}

GLdouble** transpose(GLdouble** M) {
    GLdouble** RET = new GLdouble*[4];
    for(int i = 0 ; i < 4 ; i++)
        RET[i] = new GLdouble[4];

    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            RET[j][i] = M[i][j];
        }
    }
    return RET;
}

GLdouble** GxM(GLdouble** G, GLdouble** M) {
    GLdouble** RET = new GLdouble*[2];
    for(int i = 0 ; i < 2 ; i++)
        RET[i] = new GLdouble[4];

    for(int i = 0 ; i < 2 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            RET[i][j] = 0.0;
            for(int k = 0 ; k < 4 ; k++) {
                RET[i][j] += G[i][k] * M[k][j];
            }
        }
    }
    return RET;
}

void init (void)
{
    glClearColor (WHITE, 0.0);  // Set display-window color to white.

    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, winWidth, 0.0, winHeight);
    glEnable (GL_POINT_SMOOTH);
    glPointSize(5);
    glLineWidth(3.0);

    H[0] = initPoint2D(200, 300);   // P1
    H[1] = initPoint2D(233, 500);   // P2
    H[2] = initPoint2D(400, 480);   // P3
    H[3] = initPoint2D(532, 180);   // P4

    B[0] = H[2];                    // Q0
    B[1] = initPoint2D(426, 420);   // Q1
    B[2] = initPoint2D(430, 312);   // Q2
    B[3] = initPoint2D(362, 222);   // Q3
    B[4] = initPoint2D(233, 364);   // Q4
    B[5] = H[0];                    // Q5
    // G
    for(int i = 0 ; i < 2 ; i++)
        G[i] = new GLdouble[4];
    G[0][0] = H[0].x; G[1][0] = H[0].y;
    G[0][1] = H[1].x; G[1][1] = H[1].y;
    G[0][2] = H[2].x; G[1][2] = H[2].y;
    G[0][3] = H[3].x - H[2].x; G[1][3] = H[3].y - H[2].y;

    // M
    M[0] = pointParameters(_t[0]);
    M[1] = pointParameters(_t[1]);
    M[2] = pointParameters(_t[2]);
    M[3] = vectorParameters(_t[3]);

    M = invert44(transpose(M));

    // C
    for(int i = 0 ; i < 2 ; i++)
        C[i] = new GLdouble[4];
    C = GxM(G, M);
}

GLdouble* CxT(GLdouble** C, GLdouble t) {
    GLdouble* RET = new GLdouble[2];
    GLdouble* T = pointParameters(t);
    for(int i = 0 ; i < 2 ; i++) {
        RET[i] = 0.0;
        for(int j = 0 ; j < 4 ; j++) {
            RET[i] += C[i][j] * T[j];
        }
    }
    return RET;
}

GLdouble* CxT_(GLdouble** C, GLdouble t) {
    GLdouble* RET = new GLdouble[2];
    GLdouble* T = vectorParameters(t);
    for(int i = 0 ; i < 2 ; i++) {
        RET[i] = 0.0;
        for(int j = 0 ; j < 4 ; j++) {
            RET[i] += C[i][j] * T[j];
        }
    }

    return RET;
}

void controlPolygonBezier() {
    glColor3f(BLUE);
    glLineWidth(1.0);
    glPushAttrib(GL_ENABLE_BIT);
        glLineStipple(1, 0x0F0F);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINE_STRIP);
            for(int i = 0 ; i < m ; i++){
                glVertex2f(B[i].x, B[i].y);
            }
        glEnd();
    glPopAttrib();
    glLineWidth(3.0);

    glBegin(GL_POINTS);
        for(int i = 0 ; i < m ; i++){
            glVertex2f(B[i].x, B[i].y);
        }
    glEnd();
}

void deCasteljueBezier() {
    glColor3f(BLUE);
    POINT2D *B2 = new POINT2D[m];

    for(int i = 0 ; i < m ; i++)
        B2[i] = B[i];

    glBegin(GL_LINE_STRIP);
        for(GLdouble t = 0.0 ; t <= 1.0; t+= 0.001)
            for(int j = 1 ; j < m ; j++) {
                for(int i = 0 ; i < m-j ; i++) {
                    B2[i].x = (1.0-t)*B2[i].x + t * B2[i+1].x;
                    B2[i].y = (1.0-t)*B2[i].y + t * B2[i+1].y; 
                }   
                glVertex2d(B2[0].x, B2[0].y);
            }
    glEnd();
}

void Hermite() {
    glColor3f(RED);
    glBegin(GL_POINTS);
        for (int i = 0; i < n ; i++)
            glVertex2d(H[i].x, H[i].y);
    glEnd();
    glColor3f(RED);

    glBegin(GL_LINE_STRIP);
        for(GLdouble t = _t[0] ; t <= _t[3] ; t += 0.005) {
            GLdouble* CT = CxT(C, t);
            glVertex2d(CT[0], CT[1]);
            delete CT;
        }
        glVertex2d(H[3].x, H[3].y);
    glEnd();
}

GLdouble X = 4.0/5.0;
GLdouble Y = 1-X;
void refreshPoints() {
    B[0] = H[2];
    B[5] = H[0];

    B[1] = initPoint2D(G[0][2] + G[0][3] - X*G[0][3], G[1][2] + G[1][3] - X*G[1][3]);

    GLdouble* CT = CxT_(C, _t[0]);
    B[4] = initPoint2D(G[0][0] - Y*CT[0], G[1][0] - Y*CT[1]);
    delete CT;
}

void text(const char* text, int length, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new GLdouble[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for(int i = 0 ; i < length ; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}


void draw (void)
{
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
    
    controlPolygonBezier();
    Hermite();
    refreshPoints();
    deCasteljueBezier();

    glColor3f(RED);
    for(int i = 0 ; i < 4 ; i++) {
        std::string tt = "P" + patch::to_string(i+1);
        text(tt.data(), tt.size(), H[i].x+5, H[i].y+5);
    }

    glColor3f(BLUE);
    for(int i = 0 ; i < 6 ; i++) {
        std::string tt = "Q" + patch::to_string(i);
        text(tt.data(), tt.size(), B[i].x-20, B[i].y-20);
    }

    glutSwapBuffers();
}

GLdouble dist2( POINT2D P1, POINT2D P2 ) {
    GLdouble t1 = P1.x - P2.x;
    GLdouble t2 = P1.y - P2.y;
    return t1 * t1 + t2 * t2;
}

GLint getActivePoint(GLint sens, GLint x, GLint y) {
    GLint s = sens*sens;
    POINT2D tmp = initPoint2D(x, y);

    for(int i = 0 ; i < n ; i++) {
        if(dist2(H[i], tmp) < s) {
            minus = 10;
            return i;
        }
    }
    for(int i = 0 ; i < m ; i++) {
        if(dist2(B[i], tmp) < s && (i != 1 && i != 4)) {
            minus = 0;
            return i;
        }
    }
}

void processMouse(GLint button, GLint action, GLint xMouse, GLint yMouse) {
    GLint i;

    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        if((i = getActivePoint(10, xMouse, winHeight - yMouse)) != -1) {
            dragged = i + minus;
        }
    }
    if(button == GLUT_LEFT_BUTTON && action == GLUT_UP) {
        dragged = -1;
    }
}

void setG() {
    G[0][0] = H[0].x; G[1][0] = H[0].y;
    G[0][1] = H[1].x; G[1][1] = H[1].y;
    G[0][2] = H[2].x; G[1][2] = H[2].y;
    G[0][3] = H[3].x - H[2].x; G[1][3] = H[3].y - H[2].y;
}

void processMouseActiveMotion(GLint xMouse, GLint yMouse) {
    if(dragged > 9) {
        for(int i = 0 ; i < n ; i++) {
            if(i == dragged-minus) {
                H[i].x = xMouse;
                H[i].y = winHeight - yMouse;
            }
        }
    } else {
        for(int i = 0 ; i < m ; i++) {
            if(i == dragged) {
                B[i].x = xMouse;
                B[i].y = winHeight - yMouse;
            }
        }
    }
    C = GxM(G, M);
    setG();
    glutPostRedisplay();
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
    glutMouseFunc( processMouse );
    glutMotionFunc( processMouseActiveMotion );
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}