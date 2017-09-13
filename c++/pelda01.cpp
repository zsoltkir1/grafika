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
	
	printMathObject(vecB,"B: ");
	printMathObject(vecC,"C: ");
	printMathObject(vecD,"D: ");

	printMathObject(-vecA,"negated vector: ");
	
	printf("Equal %s\n",vecC == vecD ? "True " : "False ");
	printf("Equal %s\n",vecC == vecA ? "True " : "False ");
	printf("Not Equal %s\n",vecC != vecA ? "True " : "False ");
	
	printMathObject(vecA + vecB,"Osszeg ");
	printMathObject(vecC - vecB,"Kulombseg ");
	printMathObject(vecB - vecC,"Kulombseg ");
	
	printMathObject(vecA + 5.0,"Osszeg ");
	printMathObject(vecC * 10,"Szorzat ");
	printMathObject(vecB - 2.0,"Kulombseg ");
	printMathObject(vecD / 2.0,"Osztas ");
	
	vecA *=2;
	printMathObject(vecA, "A duplája");
	
	vec3 vecA3=vec3(8.0);
	vec3 vecB3=vec3(3.0,6.0,7.0);
	vec3 vecC3=vec3(vecA,6.0);
	
	printf("Equal %s\n",vecA3 == vecB3 ? "True " : "False ");
	printMathObject(vecA3 + vecB3,"Osszeg ");
	printMathObject(vecC3 * 10,"Szorzat ");
	printMathObject(vecB3 - 2.0,"Kulombseg ");
	printMathObject(vecB3 / 2.0,"Osztas ");
	
	
	system("PAUSE");
	return 0;
}