#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

struct lapok {
	vec3 sulypont,normal;
	float lapszin,skalaris,tavolsag;
	int lappontok[4];
};

std::vector<vec3> Vaza;
std::vector<lapok> VazaLapok;
std::vector<vec4> transzormaltVaza;
std::vector<vec2> VazaDone;

mat4 forgatas, w2v, vetites, coordinateTraszfMatrix,rotatedZ, projection ,scaled, alpha;
float beta = 0.0, lepeskozfelle = 0.05,lepeskozjobbrabalra = 0.1,hengersugar = 10.0, alfa = 0.0;
float centrumpont = 20.0;
vec3 eye = { 0.0, 0.0, 0.0 }, target = { 0,0,0 }, upVector = { 0,1,0 }, Z, X, Y;
GLsizei winWidth = 1280, winHeight = 720;
GLfloat kezdoPoziX = winWidth / 2 -240, kezdoPoziY = winHeight / 2 -360, kezdoSzelesseg = 480.0f, kezdoMagassag = 480.0f;
float R = 1.5, r = 0.5;
float magassag=1;

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
	//eye.y = hengersugar * sin(degToRad(alfa));
    eye.y = magassag;
	eye.x = hengersugar * cos(degToRad(alfa));
    eye.z = -1*hengersugar * sin(degToRad(alfa));
}

void initMatrices() {
	forgatas = rotateZ(beta);
	vetites = perspective(centrumpont);
	w2v = windowToViewport3(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), vec2(kezdoPoziX, kezdoPoziY), vec2(kezdoSzelesseg, kezdoMagassag)); 
	//w2v mátrix(windows kordináta, window szélesség magasság,viewport helye, viewport szélessége magasséga)
}
vec3 fenyVektor = { 1.0,0.0,0.0 };

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
	{ 0.70f, 0.90f,0.0f },
	{ 0.00f, 0.80f ,0.0f },
	{ 0.15f, 1.60f ,0.0f },
	{ 0.45f, 1.60f,0.0f }
};
/*vec3 b_p[] = {
    { 0.15f, 0.0f,0.0f }, 
	{ 0.55f, 0.10f ,0.0f },
	{ 0.55f, 0.45f,0.0f },
	{ 0.00f, 0.40f ,0.0f },
	{ 0.10f, 0.80f ,0.0f },
	{ 0.25f, 0.80f,0.0f }
};*/


//(factorial(n) / (factorial(i-bernsteinStart)*factorial(n - (i-bernsteinStart)))

float bX(float t){
    vec3 qVec;
    int n = 5;

	qVec = {};
	for (int i = 0; i <= n; i++)
	{
		qVec += (factorial(n)/(factorial(i)*factorial(n-i))) * pow(t, i) * pow(1 - t, n - i) * b_p[i];
	}
    return qVec.x;
}

float bY(float t){
    vec3 qVec;
    int n = 5;

    qVec = {};
    for (int i = 0; i <= n; i++)
    {
		qVec += (factorial(n)/(factorial(i)*factorial(n-i))) * pow(t, i) * pow(1 - t, n - i) * b_p[i];
    }
    return qVec.y;
}


void initVaza() {
	Vaza.clear();
	/*for (double phi = 0; phi < two_pi(); phi += degToRad(18.0)) {
		for (double theta = 0; theta < two_pi(); theta += degToRad(18.0)) {
			Vaza.push_back(vec3((R + r*cos(phi))*cos(theta), (R + r*cos(phi))*sin(theta), r*sin(phi)));
			Vaza.push_back(vec3((R + r*cos(phi + degToRad(18.0)))*cos(theta), (R + r*cos(phi + degToRad(18.0)))*sin(theta), r*sin(phi + degToRad(18.0))));
			Vaza.push_back(vec3((R + r*cos(phi + degToRad(18.0)))*cos(theta + degToRad(18.0)), (R + r*cos(phi + degToRad(18.0)))*sin(theta + degToRad(18.0)), r*sin(phi + degToRad(18.0))));
			Vaza.push_back(vec3((R + r*cos(phi))*cos(theta + degToRad(18.0)), (R + r*cos(phi))*sin(theta + degToRad(18.0)), r*sin(phi)));
		}
	}*/
	float delta = 0.1;
    
	for( float theta = 0; theta < two_pi(); theta += delta*3){
        Vaza.push_back(vec3(cos(theta) * bX(0), bY(0), -sin(theta) * bX(0)));
        Vaza.push_back(vec3(cos(theta + delta*3) * bX(0), bY(0), -sin(theta + delta*3) * bX(0)));
        Vaza.push_back(vec3(0, 0, 0));
        Vaza.push_back(vec3(0, 0, 0));
        for(float bt = 0; bt <= 1; bt += delta)
            {
                Vaza.push_back(vec3(cos(theta) * bX(bt), bY(bt), -sin(theta) * bX(bt)));
                Vaza.push_back(vec3(cos(theta + delta*3) * bX(bt), bY(bt), -sin(theta + delta*3) * bX(bt)));
                Vaza.push_back(vec3(cos(theta + delta*3) * bX(bt + delta), bY(bt + delta), -sin(theta + delta*3) * bX(bt + delta)));
                Vaza.push_back(vec3(cos(theta) * bX(bt + delta), bY(bt + delta), -sin(theta) * bX(bt + delta)));
            }
        }
}

void initLapok() {
	
	VazaLapok.clear();

	lapok temp;
	for (int i = 0; i < Vaza.size(); i += 4) {
		for (int j = 0; j<4;j++){
			temp.lappontok[j] = i+j;
		}
		VazaLapok.push_back(temp);
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glShadeModel(GL_FLAT);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0);
	glLineWidth(1.5);
	initVaza();
	initLapok();
}


void rendezverajzolVazat(int i){
	if ((VazaLapok[i].skalaris > 0.0)) {
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {
					glVertex2f(VazaDone[VazaLapok[i].lappontok[j]].x, VazaDone[VazaLapok[i].lappontok[j]].y);
				}
				glEnd();
				
				glColor3f(VazaLapok[i].lapszin, VazaLapok[i].lapszin, VazaLapok[i].lapszin);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 4; j++) {
					glVertex2f(VazaDone[VazaLapok[i].lappontok[j]].x, VazaDone[VazaLapok[i].lappontok[j]].y);
				}
				glEnd();
				
			}
}

void rendezes() {
	sort(VazaLapok.begin(), VazaLapok.end(), tavolsagszerint);
	for (int i = 0; i < VazaLapok.size(); i++) {
		rendezverajzolVazat(i);		
	}
}



void kirajzol(){	
	mat4 temp = coordinateTraszfMatrix*forgatas;
	VazaDone.clear();
	transzormaltVaza.clear();
	for (int i = 0; i < Vaza.size(); i++) {
		vec4 ph = ihToH(Vaza[i]);
		vec4 pt = temp * ph;
		transzormaltVaza.push_back(pt);
	}
	
	for (int i = 0; i < VazaLapok.size(); i++) {
		int a = VazaLapok[i].lappontok[1],
			b = VazaLapok[i].lappontok[0],
			c = VazaLapok[i].lappontok[2],
			d = VazaLapok[i].lappontok[3];	
		vec3 aV = hToIh(transzormaltVaza[a]), bV = hToIh(transzormaltVaza[b]), cV = hToIh(transzormaltVaza[c]), dV = hToIh(transzormaltVaza[d]);
		
		vec3 ab = bV - aV, ac = cV - aV;

		vec3 PC = { 0 - transzormaltVaza[a].x, 0 - transzormaltVaza[a].y, centrumpont - transzormaltVaza[a].z };
		
		VazaLapok[i].normal = cross(normalize(ab), normalize(ac));
		
		VazaLapok[i].skalaris = dot(normalize(VazaLapok[i].normal), normalize(PC));
        //if (VazaLapok[i].skalaris<=0.0) VazaLapok[i].skalaris=VazaLapok[i].skalaris*-1;
        //std::cout<<VazaLapok[i].skalaris<<std::endl;
        
		vec4 temp = ihToH(fenyVektor);
		
		vec4 tempf = transpose(inverse(coordinateTraszfMatrix))*temp;
		
		vec3 szinfeny = { tempf.x, tempf.y, tempf.z };
		
        float lapszin;
        if (VazaLapok[i].skalaris<=0.0){
            VazaLapok[i].skalaris=VazaLapok[i].skalaris*-1;
            lapszin = 1-((dot(normalize(VazaLapok[i].normal), normalize(szinfeny)) + 1.0f) / 2.0f);
        }
		else{
            lapszin = (dot(normalize(VazaLapok[i].normal), normalize(szinfeny)) + 1.0f) / 2.0f;
        }
        
		
		VazaLapok[i].lapszin =lapszin;


		VazaLapok[i].sulypont = (aV + bV + cV + dV) / 4;

		vec3 centrum = { 0, 0 , centrumpont };

		VazaLapok[i].tavolsag = dist(centrum, VazaLapok[i].sulypont);
	}

	for (int i = 0; i < transzormaltVaza.size(); i++) {
		vec4 pointH = transzormaltVaza[i];
		vec4 transformedPoint = w2v *vetites*pointH;
		if (transformedPoint.w != 0)
		{
			vec3 res = hToIh(transformedPoint);
			if (res.z == 0) {
				VazaDone.push_back({ res.x, res.y });
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
		//eye.z += lepeskozfelle*5;
        magassag+=0.1;
	}
	if (keyStates['s'] && eye.z >= -30) {
		//eye.z -= lepeskozfelle*5;
        magassag-=0.1;
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
	initVaza();
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