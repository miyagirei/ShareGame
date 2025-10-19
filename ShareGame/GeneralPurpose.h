#pragma once

inline int Max3( int a, int b, int c ) { 
	int maxVal = a;
	if ( b > maxVal ) maxVal = b;
	if ( c > maxVal ) maxVal = c;

	return maxVal;
}