#include "bevgrafmath2017.h"
#include <iostream>
using namespace std;

int main(){
	vec2 vecA = vec2(5.0,10.0);
	printMathObject(vecA,"my first vector: ");
	
	printf("coordinates: %f - %f\n",vecA[0],vecA[1]);
	
	system("PAUSE");
	return 0;
}