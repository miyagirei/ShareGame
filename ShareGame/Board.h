#pragma once
#include "Tile.h"
#include <vector>

class Board {
public:
	std::vector<Tile> tiles;
	int tile_cols;
	int tile_rows;
	Board( int width, int height );

	void Draw( const Camera& camera ) const;
	const Tile* GetTileAt( double mouseX, double mouseY )const ;
};

