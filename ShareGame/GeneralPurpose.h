#pragma once

inline int Max3( int a, int b, int c ) { 
	int maxVal = a;
	if ( b > maxVal ) maxVal = b;
	if ( c > maxVal ) maxVal = c;

	return maxVal;
}

const double PI = 3.14159265358979323846264338327950288419716939937510;