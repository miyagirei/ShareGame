#pragma once
#include "Tile.h"
#include <vector>

class Board {
public:
	std::vector<Tile> tiles;

	Board( int width, int height );

	void Draw( ) const;
	Tile* GetTileAt( int mouseX, int mouseY );
};

