#include <GL/glut.h>					// (or others, depending on the system in use)
#include <time.h>  
#include <math.h>
#include <vector>

const float DEG2RAD=3.141592653589793/180;

GLsizei winWidth = 800, winHeight = 600;

typedef struct point2d { GLdouble x, y; } POINT2D;

GLint keyStates[256];

GLfloat x10 = winWidth/2, x11 = winWidth/2, y10 = 0, y11 = winHeight, x20 = 0, x21 = winWidth, y20 =winHeight/2 , y21 = winHeight/2;
GLdouble sugar=20;
double randArray[] = {-0.1, 0.1, -0.3, -0.2, -0.5, 0.5, 0.2, 0.3 ,0.4,-0.4};
float korx,kory;
std::vector<POINT2D> korok;
std::vector<POINT2D> iranyok;

GLint delta = 1;

POINT2D initPoint2D(float x, float y) {
	POINT2D P;
	P.x = x;
	P.y = y;
	return P;
}

void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);	// Set display-window color to white.
	glEnable( GL_POINT_SMOOTH );
	glLineWidth( 5.0 );
	glPointSize( 3.0 );

    glMatrixMode (GL_PROJECTION);		// Set projection parameters.
    gluOrtho2D (0.0, winWidth, 0.0, winHeight);
}

void keyPressed (unsigned char key, int x, int y) {
    keyStates[key] = 1;
}

void keyUp (unsigned char key, int x, int y) {
    keyStates[key] = 0;
}

void korrajz(float x, float y){
	glBegin(GL_POLYGON);
		for (float v = 0; v <= 360; v ++){
			float deginrad=v*DEG2RAD;
			glVertex2d(x + sugar * cos(deginrad), y + sugar * sin(deginrad));
		}
	glEnd();
}

double tavolsag(GLint x1,GLint y1,GLint x2,GLint y2, GLint i,GLint j)
{
	double ABx, ABy, APx, APy;
	double terulet, norma;
	
	ABx=x1-x2;
	ABy=y1-y2;
	
	APx = i-x2;
	APy = j-y2;
	
	terulet=(ABx*APy)-(ABy*APx);
	norma = sqrt((ABx*ABx)+(ABy*ABy));
	return terulet/norma;
}

double ponttavolsag(double x,double y,POINT2D kor){
	double diffY=kor.y-(winHeight-y);
	double diffX=kor.x-x;
	return sqrt((diffY * diffY) + (diffX * diffX));
}

void pontrajzol (void){
	glBegin( GL_POINTS );
		GLint i,j;
			for ( i = 0; i < winWidth; i+=10 )
				for ( j = 0; j < winHeight; j+=10 ){
					if ((tavolsag(x10,y10,x11,y11,i,j)<0) && (tavolsag(x20,y20,x21,y21,i,j)<0))
						{
							glColor3f( 0.5, 0.5, 0.5 );
						}
					if ((tavolsag(x10,y10,x11,y11,i,j)>0) && (tavolsag(x20,y20,x21,y21,i,j)>0))
						{
							glColor3f( 1.0, 0.0, 0.0 );
						}
					if ((tavolsag(x10,y10,x11,y11,i,j)>0) && (tavolsag(x20,y20,x21,y21,i,j)<0))
						{
							glColor3f( 0.0, 1.0, 0.0 );
						}
					if ((tavolsag(x10,y10,x11,y11,i,j)<0) && (tavolsag(x20,y20,x21,y21,i,j)>0))
						{
							glColor3f( 0.0, 0.0, 1.0 );
						}
					glVertex2f(i,j);
				}
	glEnd ( );
}

void keyOperations ( ) {
    if ((keyStates['a']) && (x10<winWidth) ) {	x10+=delta; x11-=delta;}
    if ((keyStates['d']) && (x10>0) ) {   x10-=delta; x11+=delta;}

    if ((keyStates['s']) && (y21>0) ) {	y21-=delta; y20+=delta;}
    if ((keyStates['w']) && (y21<winHeight) ) {   y21+=delta; y20-=delta;}


    glutPostRedisplay( );
}

void rajz (void)
{
	keyOperations();
    glClear (GL_COLOR_BUFFER_BIT);  // Clear display window.
	glMatrixMode(GL_PROJECTION);
	
	pontrajzol();
    glColor3f (0.0, 0.4, 0.2);      // Set line segment color to green.
    glBegin (GL_LINES);
        glVertex2i (x10, y10);       
        glVertex2i (x11, y11);
		glVertex2i (x20, y20);       
        glVertex2i (x21, y21);
	glEnd ( );
	
	for(int i=0; i<korok.size(); i++){
	   korrajz(korok[i].x, korok[i].y);
	}
	


	glutSwapBuffers();

}

POINT2D kiszamol(POINT2D irany,GLint x1,GLint y1,GLint x2,GLint y2){
	POINT2D egyenlet,vektor;
	double szam,skalarszorzat;
	skalarszorzat=(x2-x1)*irany.x+(y2-y1)*irany.y;
	szam=2*skalarszorzat/((((x2-x1)*(x2-x1))+(y2-y1)*(y2-y1)));
	egyenlet.x=szam*(x2-x1);
	egyenlet.y=szam*(y2-y1);
	vektor.x=((-1)*irany.x)+egyenlet.x;
	vektor.y=((-1)*irany.y)+egyenlet.y;
	return vektor;
}

void update(int n){
	glutPostRedisplay();
	for(int i=0; i<korok.size();i++){
		if(abs(korok[i].x+sugar>=winWidth || korok[i].x-sugar<=3)){
			iranyok[i].x*=-1;
		}
		
		if(abs(korok[i].y+sugar>=winHeight || korok[i].y-sugar<=3)){
			iranyok[i].y*=-1;
		}

		
		//if(abs(tavolsag(x10,y10,x11,y11, korok[i].x,korok[i].y))<sugar+3){
			if(abs(tavolsag(x10,y10,x11,y11, korok[i].x,korok[i].y))<=sugar){
				iranyok[i]=kiszamol(iranyok[i],x10,y10,x11,y11);				
			} 			
		//}
		//if(abs(tavolsag(x20,y20,x21,y21, korok[i].x,korok[i].y))<sugar+3){

			if(abs(tavolsag(x20,y20,x21,y21, korok[i].x,korok[i].y))<=sugar){
				iranyok[i]=kiszamol(iranyok[i],x20,y20,x21,y21);
			}
		//}	
		korok[i].y-=iranyok[i].y;
		korok[i].x-=iranyok[i].x;		
	}
	glutTimerFunc(1, update, 0);
}


void processMouse( GLint button, GLint action, int x , int y ) {
	srand(time(NULL));
	
	
	if(button==GLUT_LEFT_BUTTON && action == GLUT_DOWN){

		double iranyx=randArray[rand()%10];
		double iranyy=randArray[rand()%9+1];

		korok.push_back(initPoint2D(x,winHeight-y)); 
		iranyok.push_back(initPoint2D(iranyx,iranyy));
	}
	if(button==GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
		for(int i=0; i<korok.size();i++){
			if (ponttavolsag(x,y,korok[i])<sugar){
				korok.erase(korok.begin() + i);
				iranyok.erase(iranyok.begin() + i);
			}
		}
	}
	 

}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (0, 0);   // Set top-left display-window position.
    glutInitWindowSize (winWidth, winHeight);      // Set display-window width and height.
    glutCreateWindow ("Elso Beadando"); // Create display window.

    init ( );                            // Execute initialization procedure.
	glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
	glutDisplayFunc (rajz);       // Send graphics to display window.
	glutTimerFunc(1, update, 0);
    glutMouseFunc( processMouse );
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}