#pragma once
#include <cmath>

struct TilePosition {
	int q = 0;
	int r = 0;
};


const double HEX_RADIUS = 32.0;
const double HEX_WIDTH =  std::sqrt(3.0) * HEX_RADIUS;
const double HEX_HEIGHT = 2.0 * HEX_RADIUS;
const double HEX_VERTICAL_SPACING = 1.5 * HEX_RADIUS;

inline void TileToScreen(int q, int r,double& outX,double& outY ) { 
	outX = HEX_WIDTH * (q + 0.5 * (r & 1));
    outY = r * HEX_VERTICAL_SPACING;
}

inline TilePosition ScreenToTile( double x, double y ) { 

	int r = static_cast< int >( std::round( y / HEX_VERTICAL_SPACING ) );
	int q = static_cast< int >( std::round( ( x / HEX_WIDTH ) - 0.5 * ( r & 1 ) ) );

	return TilePosition { q,r };
}

