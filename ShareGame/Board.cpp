#include "Board.h"
#include "Dxlib.h"

Board::Board( int width, int height ) { 
	for ( int q = 0; q < width; q++ ) { 
		for ( int r = 0; r < height; r++ ) { 
			tiles.emplace_back( q, r, TileAction::None );
		}
	}

	tiles[ 2 ].action = TileAction::Heal;
	tiles[ 5 ].action = TileAction::Damage;
}

void Board::Draw() const {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY); 

	bool isClicking = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	for (auto& tile : tiles) {
		bool highlight = false;

		if (isClicking && tile.IsClicked(mouseX, mouseY)) {
			highlight = true;
		}

		tile.Draw(highlight);
	}
}

Tile* Board::GetTileAt( int mouseX, int mouseY ) { 
	for ( auto& tile : tiles ) { 
		if ( tile.IsClicked( mouseX, mouseY ) ) { 
			return &tile;
		}
	}

	return nullptr;
}