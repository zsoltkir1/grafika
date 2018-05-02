#include <GL/glut.h>
#include "bevgrafmath2017.h"
#include <vector>
#include <math.h>
#include <algorithm>
float atalakit(float deg){
	float radian=degToRad(deg);
	return(radian);
}


struct lapok {
	vec3 sulypont,normal;
	float lapszin,skalaris,tavolsag;
	bool isKockaLap;
	int lappontok[4];
};

std::vector<vec3> torus;
std::vector<lapok> torusLapok;
std::vector<lapok> mindenLap;
std::vector<vec4> transzormaltTorus;
std::vector<vec2> torusDone;


mat4 forgatas, w2v, vetites, coordinateTraszfMatrix,rotatedZ, projection ,scaled, alpha;
float beta = 0.0, lepeskozfelle = 0.05,lepeskozjobbrabalra = 0.1,hengersugar = 10.0, alfa = 0.0;

float centrumpont = 20.0;
vec3 eye = { 0.0, 0.0, 0.0 }, target = { 0,0,0 }, upVector = { 0,0,1 }, Z, X, Y;
bool isCentral = false;
GLsizei winWidth = 1280, winHeight = 720;
GLfloat kezdoPoziX = winWidth / 2 -100, kezdoPoziY = winHeight / 2 -100, kezdoSzelesseg = 200.0f, kezdoMagassag = 200.0f;

float R = 1.5, r = 0.5;

vec4 kockaTrUtan[8];
vec2 rajzolhatoKocka[8] = {};
//lapok kockalapok[8];
std::vector<lapok> kockalapok;

bool zkoordinataszerint(lapok a, lapok b)
{
	return a.sulypont.z < b.sulypont.z;
}

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
	eye.y = hengersugar * sin(atalakit(alfa));
	eye.x = hengersugar * cos(atalakit(alfa));
}

vec3 kockaElek[8] = {
	{ -0.5,-0.5,0.5 },//pirosfeherzold
	{ 0.5,-0.5,0.5 },//pirossargazold
	{ 0.5,0.5,0.5 },//pirossargakek
	{ -0.5,0.5,0.5 },//piroskekfeher
	{ -0.5,-0.5,-0.5 },//narancsfeherzold
	{ -0.5,0.5,-0.5 },//narancskekfeher
	{ 0.5,0.5,-0.5 },//narancssargakek
	{ 0.5,-0.5,-0.5 }//narancssargazold
};

void initLapok() {
	
	int rubiklapok[6][4] = {
		{ 0,1,2,3 },
		{ 3,2,6,5 },
		{ 1,7,6,2 },
		{ 7,4,5,6 },	
		{ 4,0,3,5 },
		{ 4,7,1,0 }
	};
	
	kockalapok.clear();
	for (int i = 0; i < 6; i++) {
		lapok temp;
		for (int j = 0; j <4; j++){	
			temp.lappontok[j] = rubiklapok[i][j];
		}
		kockalapok.push_back(temp);
	}
	
	torusLapok.clear();

	lapok temp;
	for (int i = 0; i < torus.size(); i += 4) {
		for (int j = 0; j<4;j++){
			temp.lappontok[j] = i+j;
		}
		torusLapok.push_back(temp);
	}
}

void rendezverajzolkockat(int i){
	if ((mindenLap[i].skalaris > 0.0  && isCentral == true) || (mindenLap[i].normal.z > 0.0 && isCentral == false)) {		
				glColor3f(0.0, 1.0, 0.0);
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {

					glVertex2f(rajzolhatoKocka[mindenLap[i].lappontok[j]].x, rajzolhatoKocka[mindenLap[i].lappontok[j]].y);
				}
				glEnd();
				
				glColor3f(mindenLap[i].lapszin, mindenLap[i].lapszin, mindenLap[i].lapszin);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 4; j++) {
					glVertex2f(rajzolhatoKocka[mindenLap[i].lappontok[j]].x, rajzolhatoKocka[mindenLap[i].lappontok[j]].y);
				}
				glEnd();

			}
}

void rendezverajzoltoruszt(int i){
	if ((mindenLap[i].skalaris > 0.0  && isCentral == true) || (mindenLap[i].normal.z > 0.0 && isCentral == false)) {
				glColor3f(0.0, 1.0, 0.0);
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {

					glVertex2f(torusDone[mindenLap[i].lappontok[j]].x, torusDone[mindenLap[i].lappontok[j]].y);
				}
				glEnd();
				
				glColor3f(mindenLap[i].lapszin, mindenLap[i].lapszin, mindenLap[i].lapszin);
				glBegin(GL_POLYGON);
				for (int j = 0; j < 4; j++) {
					glVertex2f(torusDone[mindenLap[i].lappontok[j]].x, torusDone[mindenLap[i].lappontok[j]].y);
				}
				glEnd();
				
			}
}

void rendezes() {
	mindenLap.clear();
	int z=kockalapok.size()+torusLapok.size();
	for (int i = 0; i < (z+1); i++) {
		if (i<(kockalapok.size()+1)){
		mindenLap.push_back(kockalapok[i]);
		}
		if (i>kockalapok.size()){
			mindenLap.push_back(torusLapok[i-kockalapok.size()-1]);
		}
	}

	if (isCentral == false) {
		sort(mindenLap.begin(), mindenLap.end(), zkoordinataszerint);
	}
	else {
		sort(mindenLap.begin(), mindenLap.end(), tavolsagszerint);
	}

	for (int i = 0; i < mindenLap.size(); i++) {
		if (mindenLap[i].isKockaLap == true) {
			rendezverajzolkockat(i);
		}
		else {
			rendezverajzoltoruszt(i);
		}
	}


}

vec2 decastPoints[5][5];
vec2 decastPoints2[10]={{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

void decasteljauBezier(){	   
    int bezierhossz = 5;
	for (float u = 0.0; u < 1.0; u += 0.1) {
		for (int gen = 1; gen <= bezierhossz; gen++) {
			for (int i = 0; i <= (bezierhossz - 1) - gen; i++) {
				decastPoints[gen][i] = (1 - u)*decastPoints[gen - 1][i] + u*decastPoints[gen - 1][i + 1];
			}
		}
        int k=u*10;
        decastPoints2[k]={decastPoints[4][0].x,decastPoints[4][0].y};
		//glVertex2f(decastPoints[4][0].x, decastPoints[4][0].y);
	}
}

void initTorus() {
	torus.clear();
	/*for (double phi = 0; phi < two_pi(); phi += atalakit(18.0)) {
		for (double theta = 0; theta < two_pi(); theta += atalakit(18.0)) {
			torus.push_back(vec3((R + r*cos(phi))*cos(theta), (R + r*cos(phi))*sin(theta), r*sin(phi)));
			torus.push_back(vec3((R + r*cos(phi + atalakit(18.0)))*cos(theta), (R + r*cos(phi + atalakit(18.0)))*sin(theta), r*sin(phi + atalakit(18.0))));
			torus.push_back(vec3((R + r*cos(phi + atalakit(18.0)))*cos(theta + atalakit(18.0)), (R + r*cos(phi + atalakit(18.0)))*sin(theta + atalakit(18.0)), r*sin(phi + atalakit(18.0))));
			torus.push_back(vec3((R + r*cos(phi))*cos(theta + atalakit(18.0)), (R + r*cos(phi))*sin(theta + atalakit(18.0)), r*sin(phi)));
		}
	}*/
    decasteljauBezier();
    for (int phi = 0; phi < 10; phi += 1) {
		for (double theta = 0; theta < two_pi(); theta += atalakit(18.0)) {
			torus.push_back(vec3(cos(theta)*decastPoints2[phi].x, decastPoints2[phi].y,-sin(65)*decastPoints2[phi].x ));
            torus.push_back(vec3(cos(theta + atalakit(18.0))*decastPoints2[phi].x, decastPoints2[phi].y,-sin(65+ atalakit(18.0))*decastPoints2[phi].x ));
            torus.push_back(vec3(cos(theta+ atalakit(18.0))*decastPoints2[phi].x + atalakit(18.0), decastPoints2[phi].y,-sin(65 + atalakit(18.0))*decastPoints2[phi].x ));
            torus.push_back(vec3(cos(theta + atalakit(18.0))*decastPoints2[phi].x, decastPoints2[phi].y,-sin(65)*decastPoints2[phi].x ));
			//torus.push_back(vec3((R + r*cos(phi + atalakit(18.0)))*cos(theta), (R + r*cos(phi + atalakit(18.0)))*sin(theta), r*sin(phi + atalakit(18.0))));
			//torus.push_back(vec3((R + r*cos(phi + atalakit(18.0)))*cos(theta + atalakit(18.0)), (R + r*cos(phi + atalakit(18.0)))*sin(theta + atalakit(18.0)), r*sin(phi + atalakit(18.0))));
			//torus.push_back(vec3((R + r*cos(phi))*cos(theta + atalakit(18.0)), (R + r*cos(phi))*sin(theta + atalakit(18.0)), r*sin(phi)));
		}
	}
}

void initMatrices() {
	forgatas = rotateZ(beta);
	if (isCentral == true){
		vetites = perspective(centrumpont);
		
	}
	else {
		vetites = ortho();
	}
	w2v = windowToViewport3(vec2(-1.0f, -1.0f), vec2(2.0f, 2.0f), vec2(kezdoPoziX, kezdoPoziY), vec2(kezdoSzelesseg, kezdoMagassag)); //w2v mátrix(windows kordináta, window szélesség magasság,viewport helye, viewport szélessége magasséga)
}
vec3 fenyVektor = { 0.0,0.0,1.0 };

void kirajzol(){

	for (int i = 0; i < 8; i++) {
		vec4 pointH = ihToH(kockaElek[i]);
		vec4 transformedPoint = coordinateTraszfMatrix*pointH;
		kockaTrUtan[i] = transformedPoint;
	}
	
	vec3 ab, ac;
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
	}
	
	mat4 temp = coordinateTraszfMatrix*forgatas;
	torusDone.clear();
	transzormaltTorus.clear();
	for (int i = 0; i < torus.size(); i++) {
		vec4 ph = ihToH(torus[i]);
		vec4 pt = temp * ph;
		transzormaltTorus.push_back(pt);
	}
	
	for (int i = 0; i < torusLapok.size(); i++) {
		torusLapok[i].isKockaLap = false;
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
	if (keyStates['j']) {
		r += 0.01;
	}
	if (keyStates['k']) {
		r -= 0.01;
	}
	if (keyStates['u']) {
		R+=0.01;
	}
	if (keyStates['i']) {
		R -= 0.01;
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

	if (keyStates[VK_TAB]){ 
		if (isCentral == true){
			isCentral = false;
		}
		else{
			isCentral = true;
		}
	}
	
	if (keyStates['0']) {
		isCentral = false;
	}
	if (keyStates['1']) {
		isCentral = true;
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
	initMatrices();
}

int N = 5;
vec3 pyramid[5] = {};
vec2 drawablePyramid[5] = {};

void initPyramid(){
    
    int idx = 0;
    float r = 1;
    float step = 2 * pi() / 4;
    
    for ( float t = 0; idx < N - 1; t += step){
        
        pyramid[idx].x = cos(t) * r;
        pyramid[idx].y = sin(t) * r;
        pyramid[idx].z = 0.5;
        idx++;
    }
    
    pyramid[4].x = 0; pyramid[4].y = 0; pyramid[4].z = 2.5;

}
void drawPyramid(){
    
    glBegin(GL_POINTS);
    for (int i = 0; i < N; i++){
        glVertex2f(drawablePyramid[i].x, drawablePyramid[i].y);
        glVertex2f(drawablePyramid[i].x, drawablePyramid[i].y);
    }
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < N - 1; i++){
        glVertex2f(drawablePyramid[i].x, drawablePyramid[i].y);
    }
    glEnd();
    
    glBegin(GL_LINES);
    for (int i = 0; i < N - 1; i++){
        glVertex2f(drawablePyramid[i].x, drawablePyramid[i].y);
        glVertex2f(drawablePyramid[N - 1].x, drawablePyramid[N - 1].y);
    }
    glEnd();
    
}
void transform(){
    
    mat4 M = w2v * projection * scaled;

    for ( int i = 0; i < N; i++ ){
        
        vec4 pointH = ihToH( pyramid[i] );
        vec4 transformedPoint = M * pointH;
        
        if(transformedPoint.w != 0){
            vec3 result = hToIh(transformedPoint);
            if(result.z == 0){
                drawablePyramid[i] = { result.x, result.y };
            }
        }
        
    }
    
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