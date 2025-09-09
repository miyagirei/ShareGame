#pragma once
#include <cmath>

struct TilePosition {
	int q = 0;
	int r = 0;
};

constexpr double TILE_WIDTH = 64.0;
constexpr double TILE_HEIGHT = 56.0;

constexpr double TILE_HORIZONTAL_OFFSET_RATIO = 0.75;
constexpr double TILE_VERTICAL_OFFSET_RATIO = 0.5;

inline void TileToScreen(int q, int r,double& outX,double& outY ) { 
	outX = TILE_WIDTH * ( TILE_HORIZONTAL_OFFSET_RATIO * q );
	outY = TILE_HEIGHT * ( r + q * TILE_VERTICAL_OFFSET_RATIO );
}

inline TilePosition ScreenToTile( double x, double y ) { 
	double width3_4 = TILE_WIDTH * TILE_HORIZONTAL_OFFSET_RATIO;
	double heightHalf = TILE_HEIGHT * TILE_VERTICAL_OFFSET_RATIO;

	double q_double = x / width3_4;
	double r_double = (y - (q_double * heightHalf)) / TILE_HEIGHT;

	int q = ( int )std::round( q_double );
	int r = ( int )std::round( r_double );

	return TilePosition { q,r };
}

