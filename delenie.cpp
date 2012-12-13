#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
int main()
{
	float a=2.0;
	float b=5.2;
	double *i;
	int c = (int) b;
	a= modf( b,  i);
	// //a= a%b;
	// cout<<a<<endl;
	return 0;
}
