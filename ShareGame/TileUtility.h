#pragma once
struct TilePosition {
	int q = 0;
	int r = 0;
};

constexpr double TILE_WIDTH = 64.0;
constexpr double TILE_HEIGHT = 56.0;

constexpr double TILE_HORIZONTAL_OFFSET_RATIO = 0.75;
constexpr double TILE_VARTICAL_OFFSET_RATIO = 0.5;

inline void TileToScreen(int q, int r,double& outX,double& outY ) { 
	outX = TILE_WIDTH * ( TILE_HORIZONTAL_OFFSET_RATIO * q );
	outY = TILE_HEIGHT * ( r + q * TILE_VARTICAL_OFFSET_RATIO );
}

