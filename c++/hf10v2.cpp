#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <vector>
#include <math.h>
#include <algorithm>

struct lapok {
	vec3 sulypont,normal;
	float lapszin,skalaris,tavolsag;
	int lappontok[4];
};

std::vector<vec3> torus;
std::vector<lapok> torusLapok;
std::vector<vec4> transzormaltTorus;
std::vector<vec2> torusDone;

mat4 forgatas, w2v, vetites, coordinateTraszfMatrix,rotatedZ, projection ,scaled, alpha;
float beta = 0.0, lepeskozfelle = 0.05,lepeskozjobbrabalra = 0.1,hengersugar = 10.0, alfa = 0.0;
float centrumpont = 20.0;
vec3 eye = { 0.0, 0.0, 0.0 }, target = { 0,0,0 }, upVector = { 0,0,1 }, Z, X, Y;
GLsizei winWidth = 1280, winHeight = 720;
GLfloat kezdoPoziX = winWidth / 2 -100, kezdoPoziY = winHeight / 2 -100, kezdoSzelesseg = 200.0f, kezdoMagassag = 200.0f;
float R = 1.5, r = 0.5;

bool tavolsagszerint(lapok a, lapok b) {

	return a.tavolsag > b.tavolsag;
}

void cameraTranszformacio() {
	Z = normalize((eye - target));
	X = normalize(cross(upVector, Z)); 
	Y = normalize(cross(Z, X));
	vec3 d = eye;
	coordinateTraszfMatrix = coordinateTransform(d, X, Y, Z);
}

void cameraSzamol() {
	eye.y = hengersugar * sin(degToRad(alfa));
	eye.x = hengersugar * cos(degToRad(alfa));
}

void initMatrices() {
	forgatas = rotateZ(beta);
	vetites = perspective(centrumpont);
	w2v = windowToViewport3(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), vec2(kezdoPoziX, kezdoPoziY), vec2(kezdoSzelesseg, kezdoMagassag)); 
	//w2v mátrix(windows kordináta, window szélesség magasság,viewport helye, viewport szélessége magasséga)
}
vec3 fenyVektor = { 0.0,0.0,1.0 };

int factorial(int f) {
	int factorial = 1;
	for (int i = 1; i <= f; i++) {
		factorial *= i;
	}
	return factorial;
}

vec3 b_p[6] = {
	{ 0.30f, 0.0f,0.0f }, 
	{ 1.10f, 0.20f ,0.0f },
	{ 1.10f, 0.90f,0.0f },
	{ 0.15f, 0.80f ,0.0f },
	{ 0.15f, 1.60f ,0.0f },
	{ 0.45f, 1.60f,0.0f }
};

//(factorial(n) / (factorial(i-bernsteinStart)*factorial(n - (i-bernsteinStart)))

float b_x(float t){
    vec3 qVec;
    int n = 5;

	qVec = {};
	for (int i = 0; i <= n; i++)
	{
		//qVec += under(n, i) * pow(t, i) * pow(1 - t, n - i); * b_p[i];
		qVec += (factorial(n)/(factorial(i)*factorial(n-i))) * pow(t, i) * pow(1 - t, n - i) * b_p[i];
	}
    return qVec.x;
}

float b_y(float t){
    vec3 qVec;
    int n = 5;

    qVec = {};
    for (int i = 0; i <= n; i++)
    {
        //qVec += under(n, i) * pow(t, i) * pow(1 - t, n - i); * b_p[i];
		qVec += (factorial(n)/(factorial(i)*factorial(n-i))) * pow(t, i) * pow(1 - t, n - i) * b_p[i];
    }
    return qVec.y;
}


void initTorus() {
	torus.clear();
	/*for (double phi = 0; phi < two_pi(); phi += degToRad(18.0)) {
		for (double theta = 0; theta < two_pi(); theta += degToRad(18.0)) {
			torus.push_back(vec3((R + r*cos(phi))*cos(theta), (R + r*cos(phi))*sin(theta), r*sin(phi)));
			torus.push_back(vec3((R + r*cos(phi + degToRad(18.0)))*cos(theta), (R + r*cos(phi + degToRad(18.0)))*sin(theta), r*sin(phi + degToRad(18.0))));
			torus.push_back(vec3((R + r*cos(phi + degToRad(18.0)))*cos(theta + degToRad(18.0)), (R + r*cos(phi + degToRad(18.0)))*sin(theta + degToRad(18.0)), r*sin(phi + degToRad(18.0))));
			torus.push_back(vec3((R + r*cos(phi))*cos(theta + degToRad(18.0)), (R + r*cos(phi))*sin(theta + degToRad(18.0)), r*sin(phi)));
		}
	}*/
	float delta = 0.1;
	for( float theta = 0; theta < two_pi(); theta += delta){
            for(float bt = 0; bt <= 1; bt += delta)
            {
                torus.push_back(vec3(cos(theta) * b_x(bt), b_y(bt), -sin(theta) * b_x(bt)));
                torus.push_back(vec3(cos(theta + delta) * b_x(bt), b_y(bt), -sin(theta + delta) * b_x(bt)));
                torus.push_back(vec3(cos(theta + delta) * b_x(bt + delta), b_y(bt + delta), -sin(theta + delta) * b_x(bt + delta)));
                torus.push_back(vec3(cos(theta) * b_x(bt + delta), b_y(bt + delta), -sin(theta) * b_x(bt + delta)));
            }
        }
}

void initLapok() {
	
	torusLapok.clear();

	lapok temp;
	for (int i = 0; i < torus.size(); i += 4) {
		for (int j = 0; j<4;j++){
			temp.lappontok[j] = i+j;
		}
		torusLapok.push_back(temp);
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
	glLineWidth(1.0);
	initTorus();
	initLapok();
	//initMatrices();
}


void rendezverajzoltoruszt(int i){
	if ((torusLapok[i].skalaris > 0.0)) {
				glColor3f(0.0, 1.0, 0.0);
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {
					glVertex2f(torusDone[torusLapok[i].lappontok[j]].x, torusDone[torusLapok[i].lappontok[j]].y);
				}
				glEnd();
				
				glColor3f(torusLapok[i].lapszin, torusLapok[i].lapszin, torusLapok[i].lapszin);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 4; j++) {
					glVertex2f(torusDone[torusLapok[i].lappontok[j]].x, torusDone[torusLapok[i].lappontok[j]].y);
				}
				glEnd();
				
			}
}

void rendezes() {
	sort(torusLapok.begin(), torusLapok.end(), tavolsagszerint);
	for (int i = 0; i < torusLapok.size(); i++) {
		rendezverajzoltoruszt(i);		
	}
}



void kirajzol(){

	/*for (int i = 0; i < 8; i++) {
		vec4 pointH = ihToH(kockaElek[i]);
		vec4 transformedPoint = coordinateTraszfMatrix*pointH;
		kockaTrUtan[i] = transformedPoint;
	}*/
	
	/*vec3 ab, ac;
	for (int i = 0; i < kockalapok.size(); i++) {
		kockalapok[i].isKockaLap = true;
		int b = kockalapok[i].lappontok[1], a = kockalapok[i].lappontok[0], c = kockalapok[i].lappontok[3], d = kockalapok[i].lappontok[2];
		vec3 aV = hToIh(kockaTrUtan[a]), bV = hToIh(kockaTrUtan[b]), cV = hToIh(kockaTrUtan[c]), dV = hToIh(kockaTrUtan[d]);
		ab = bV - aV;
		ac = cV - aV;


		vec3 PC = { 0 - kockaTrUtan[a].x, 0 - kockaTrUtan[a].y, centrumpont - kockaTrUtan[a].z };
		
		kockalapok[i].normal = cross(normalize(ab), normalize(ac));
		
		kockalapok[i].skalaris = dot(normalize(kockalapok[i].normal), normalize(PC));

		vec4 temp = ihToH(fenyVektor);
		
		vec4 tempf = transpose(inverse(coordinateTraszfMatrix))*temp;

		vec3 szinfeny = { tempf.x, tempf.y, tempf.z };

		float lapszin = (dot(normalize(kockalapok[i].normal), normalize(szinfeny)) + 1.0f) / 2.0f;
		
		kockalapok[i].lapszin = lapszin;

		kockalapok[i].sulypont = (aV + bV + cV + dV) / 4;

		vec3 centrum = { 0,0,centrumpont };

		kockalapok[i].tavolsag = dist(centrum, kockalapok[i].sulypont);
	}

	for (int i = 0; i < 8; i++) {
		vec4 pointH = kockaTrUtan[i];
		vec4 transformedPoint = w2v *vetites*pointH;
		if (transformedPoint.w != 0)
		{
			vec3 res = hToIh(transformedPoint);
			if (res.z == 0) {
				rajzolhatoKocka[i] = { res.x, res.y };
			}
		}
	}*/
	
	mat4 temp = coordinateTraszfMatrix*forgatas;
	torusDone.clear();
	transzormaltTorus.clear();
	for (int i = 0; i < torus.size(); i++) {
		vec4 ph = ihToH(torus[i]);
		vec4 pt = temp * ph;
		transzormaltTorus.push_back(pt);
	}
	
	for (int i = 0; i < torusLapok.size(); i++) {
		int a = torusLapok[i].lappontok[1],
			b = torusLapok[i].lappontok[0],
			c = torusLapok[i].lappontok[2],
			d = torusLapok[i].lappontok[3];	
		vec3 aV = hToIh(transzormaltTorus[a]), bV = hToIh(transzormaltTorus[b]), cV = hToIh(transzormaltTorus[c]), dV = hToIh(transzormaltTorus[d]);
		
		vec3 ab = bV - aV, ac = cV - aV;

		vec3 PC = { 0 - transzormaltTorus[a].x, 0 - transzormaltTorus[a].y, centrumpont - transzormaltTorus[a].z };
		
		torusLapok[i].normal = cross(normalize(ab), normalize(ac));
		
		torusLapok[i].skalaris = dot(normalize(torusLapok[i].normal), normalize(PC));

		vec4 temp = ihToH(fenyVektor);
		
		vec4 tempf = transpose(inverse(coordinateTraszfMatrix))*temp;
		
		vec3 szinfeny = { tempf.x, tempf.y, tempf.z };
		
		float lapszin = (dot(normalize(torusLapok[i].normal), normalize(szinfeny)) + 1.0f) / 2.0f;
		
		torusLapok[i].lapszin =lapszin;


		torusLapok[i].sulypont = (aV + bV + cV + dV) / 4;

		vec3 centrum = { 0, 0 , centrumpont };

		torusLapok[i].tavolsag = dist(centrum, torusLapok[i].sulypont);
	}

	for (int i = 0; i < transzormaltTorus.size(); i++) {
		vec4 pointH = transzormaltTorus[i];
		vec4 transformedPoint = w2v *vetites*pointH;
		if (transformedPoint.w != 0)
		{
			vec3 res = hToIh(transformedPoint);
			if (res.z == 0) {
				torusDone.push_back({ res.x, res.y });
			}
		}

	}
}

GLint keyStates[256];
void keyboard(unsigned char key, int x, int y) {
	keyStates[key] = 1;
}
void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = 0;
}
void billentyuMuveletek() {
	if (keyStates[27]) {
		exit(0);
	}
	if (keyStates['a']) {
		alfa += lepeskozjobbrabalra*5;
	}
	if (keyStates['d']) {
		alfa -= lepeskozjobbrabalra*5;
	}
	if (keyStates['w'] && eye.z <= 30) {
		eye.z += lepeskozfelle*5;
	}
	if (keyStates['s'] && eye.z >= -30) {
		eye.z -= lepeskozfelle*5;
	}
	if (keyStates['-']) {
		centrumpont -= centrumpont/1000;
	}
	if (keyStates['+']) {
		centrumpont += centrumpont/1000;
	}
	if (keyStates['y']) {
		hengersugar += 0.1;
	}
	if (keyStates['x']) {
		hengersugar -= 0.1;
	}
	glutPostRedisplay();
}

void update(int n) {
	//beta += 0.005;
	glutPostRedisplay();
	glutTimerFunc(100, update, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	billentyuMuveletek();
	initMatrices();
	cameraSzamol();
	cameraTranszformacio();
	initTorus();
	kirajzol();
	rendezes();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Beadando_720P");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(100, update, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutMainLoop();
	return 0;
}