#pragma once
#include "Tile.h"
#include <vector>

class Board {
public:
	std::vector<Tile> tiles;

	Board( int width, int height );

	void Draw(const Camera& camera ) const;
	Tile* GetTileAt( int mouseX, int mouseY );
};

