#include "bevgrafmath2017.h"
#include <iostream>
using namespace std;

int main(){
	vec2 vecA = vec2(5.0,10.0);
	printMathObject(vecA,"my first vector: ");
	
	printf("coordinates: %f - %f\n",vecA[0],vecA[1]);
	
	vec2 vecB=vec2(8.0,2.0);
	vec2 vecC=vec2(3.0,6.0);
	vec2 vecD=vec2(3.0,6.0);

	printMathObject(-vecA,"negated vector: ");
	
	printf("Equal %s\n",vecC == vecD ? "True" : "False");
	printf("Equal %s\n",vecC == vecA ? "True" : "False");
	printf("Not Equal %s\n",vecC != vecA ? "True" : "False");
	
	printMathObject(vecA + vecB,"Osszeg");
	printMathObject(vecC - vecB,"Kulombseg");
	printMathObject(vecB - vecC,"Kulombseg");
	
	system("PAUSE");
	return 0;
}