#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <math.h>
#include <vector>
#include<iostream>
#include <string>  
using namespace std;
struct faces4 {
	int p[4];
	vec3 normal;
};
GLint keyStates[256];
GLsizei winWidth = 800, winHeight = 600;
mat4 rotationX, rotationY, rotationZ, Mk, Mt, w2v, projection, CameraMatrix;
vector<vec3> torusBase;
vector<vec2> torusCalculated;
float alpha = 0.0, beta = 0.0, stepinterval = 0.005/*degToRad(1.0f)*/;
float rCamera = 10, magassag = 0, alfaCamera = 30.0;
float CameraX = rCamera*cos(degToRad(alfaCamera));
float CameraY = rCamera*sin(degToRad(alfaCamera));
float CameraZ = magassag;
vec3 Camera = { CameraX, CameraY, CameraZ }, target = { 0,0,0 }, up = { 0,0,1 }, Zaxis, Xaxis, Yaxis;
int stateChange = 1;
int N = 8;
GLfloat cX = winWidth / 2, cY = winHeight / 2, cW = 45.0f, cH = 45.0f;
int lepeskoz = two_pi() / degToRad(15.0);
float R = 5, r = 1;
int cubefaces[6][4] = {
	{ 0,1,2,3 },
	{ 1,5,6,2 },
	{ 5,4,7,6 },
	{ 4,0,3,7 },
	{ 7,6,2,3 },
	{ 4,1,5,0 }
};
vec3 cube12[8] = {
	{ -1,-1,1 },//0
	{ 1,-1,1 }, //1
	{ 1,1,1 },	//2
	{ -1,1,1 }, //3
	{ -1,-1,-1 },//4
	{ 1,-1,-1 }, //5
	{ 1,1,-1 },  //6
	{ -1,1,-1 }, //7
};
vec2 drawableCube[8] = {};
void szoveg(GLfloat x, GLfloat y, string string)
{
	GLint hossz, i;
	//cout << "DFASDFASDF " << string << endl;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	hossz = (GLint)string.length();
	for (i = 0; i < hossz; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}
void cameraSzamol() {
	CameraX = rCamera * cos(degToRad(alfaCamera));
	CameraY = rCamera * sin(degToRad(alfaCamera));
	CameraZ = magassag;

	Camera.x = CameraX;
	Camera.y = CameraY;
	Camera.z = CameraZ;
}
void createCameraTransFormation() {
	Zaxis = normalize(Camera - target);
	Xaxis = normalize(cross(up, Zaxis));
	Yaxis = cross(Zaxis, Xaxis);
	CameraMatrix = coordinateTransform(Camera, Xaxis, Yaxis, Zaxis);
	//printMathObject(CameraMatrix, "Fuck you: ");
	//Yaxis = normalize(Yaxis);

}
void initTorusBase() {
	torusBase.clear();
	for (double theta = 0; theta < two_pi(); theta += degToRad(15.0))
	{
		for (double phi = 0; phi < two_pi(); phi += degToRad(15.0))
		{
			//vec3 pih = vec3(cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi));
			vec3 pih = vec3(
				(R + r*cos(phi))*cos(theta),
				(R + r*cos(phi))*sin(theta),
				r*sin(phi)
			);
			torusBase.push_back(pih);
			/*
			vec4 ph = ihToH(pih);
			vec4 pt = Mk * ph;
			if (pt.w != 0)
			{
				vec3 ptih = hToIh(pt);

				//glVertex2f(ptih.x, ptih.y);
			}
			*/
		}

	}
	//cout << "Torus base: " << torusBase.size() << endl;
}
void initMatrices() {
	rotationZ = rotateZ(beta);
	if (stateChange == 1) {
		projection = ortho();
	}
	else if (stateChange == 2) {
		projection = perspective(5.0);
	}
	w2v = windowToViewport3(vec2(-1.0f, -1.0f), vec2(1.0f, 1.0f), vec2(cX, cY), vec2(cW, cH));
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0);
	glLineWidth(1.0);
	initTorusBase();
	initMatrices();
}

void drawCube() {
	Mk = w2v *projection * CameraMatrix;
	for (int i = 0; i < N; i++) {
		vec4 pointH = ihToH(cube12[i]);
		vec4 transformedPoint = Mk*pointH;
		if (transformedPoint.w != 0)
		{
			vec3 res = hToIh(transformedPoint);
			if (res.z == 0) {
				drawableCube[i] = { res.x, res.y };
			}
		}
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();
	glColor3f(1.000, 0.271, 0.000);
	glBegin(GL_POINTS);
	for (int i = 1; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			glVertex2f(drawableCube[cubefaces[i][j]].x, drawableCube[cubefaces[i][j]].y);
		}
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < N / 2; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int i = (N / 2); i < N; i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < (N / 2); i++) {
		glVertex2f(drawableCube[i].x, drawableCube[i].y);
		glVertex2f(drawableCube[i + 4].x, drawableCube[i + 4].y);
	}
	glEnd();


}
void drawTorus() {
	glLineWidth(2.0f);

	Mt = w2v *projection * CameraMatrix*rotationZ;

	glColor3f(0.0f, 0.1f, 0.9f);
	torusCalculated.clear();
	for (int i = 0; i < torusBase.size(); i++) {
		vec4 ph = ihToH(torusBase[i]);
		vec4 pt = Mt * ph;
		if (pt.w != 0) {
			vec3 ptih = hToIh(pt);
			if (ptih.z == 0) {
				torusCalculated.push_back({ ptih.x, ptih.y });
			}
		}
	}

	
	////////////////////////////////////////////////////////////////////

	//hosszúsági körök kirajzolása ez már tuti jó
	/*
	int limit = lepeskoz;
	for (int i = 0; i < torusBase.size(); i += lepeskoz) {
		glBegin(GL_LINE_LOOP);
		//glBegin(GL_POINTS);
		cout << "1) i: " << i << " limit: " << limit << endl;
		for (int oszlop = i; oszlop< limit; oszlop++) {
				glVertex2f(torusCalculated[oszlop].x, torusCalculated[oszlop].y);
		}
		glEnd();
		limit += lepeskoz;
		cout <<"2) i: "<<i<<" limit: " << limit << endl;
	}
	*/
	
	// glBegin(GL_POINTS);
	for (int szint = 0; szint <lepeskoz; szint++) {
		glBegin(GL_LINE_LOOP);
		//cout << "szint: " << szint << endl;
		for (int i = szint; i < torusBase.size(); i += lepeskoz) {
			glVertex2f(torusCalculated[i].x, torusCalculated[i].y);

		}
		glEnd();
		//limit += lepeskoz;
	}

	////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////
	//szélességi körök kirajzolása ez már jó



	///////////////////////////////////////////////////////////////////
}
void leptetes()
{
	//cout << "BBB" << endl;
	if (keyStates['a']) {
		//cout << "a: " << beta <<endl;
		alfaCamera -= stepinterval;
	}
	if (keyStates['d']) {
		//cout << "d: " << beta << endl;
		alfaCamera += stepinterval;
	}
	if (keyStates['w'] && magassag <= 10) {
		magassag += stepinterval;
		//cout << "w: " << alpha << endl;
	}
	if (keyStates['s'] && magassag >= -10) {
		magassag -= stepinterval;
		//cout << "s: " << alpha << endl;
	}
	if (keyStates['r']) {
		stateChange = 1;
		//cout << "w: " << alpha << endl;
	}
	if (keyStates['t']) {
		stateChange = 2;
		//cout << "s: " << alpha << endl;
	}
	if (keyStates[27]) {
		exit(0);

	}

	glutPostRedisplay();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	initMatrices();
	//cout << "AAA" << endl;
	cameraSzamol();
	createCameraTransFormation();
	leptetes();
	drawCube();
	drawTorus();
	glutSwapBuffers();
}
void update(int n) {
	beta += 0.01;
	if (degToRad(beta) == two_pi()) {
		cout << "nagy " << degToRad(beta) << endl;
		beta = 0.0;
	}
	//cout << beta << endl;
	glutPostRedisplay();
	glutTimerFunc(50, update, 0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("Kocka");

	init();
	glutDisplayFunc(display);
	//glutTimerFunc(50, update, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}




