#include "Board.h"
#include "Tile.h"
#include "DxLib.h"

Board::Board( int width, int height ):
tile_cols(width),
tile_rows(height){ 
	for ( int q = 0; q < width; ++q ) { 
		for ( int r = 0; r < height; ++r ) { 
			Tile tile( q, r, TileAction::None );
			tiles.emplace_back( tile );
		}
	}

	tiles[ 12 ].action = TileAction::Heal;
	tiles[ 15 ].action = TileAction::Damage;
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

Tile* Board::GetTileAt( double mouseX, double mouseY ) {


	TilePosition pos = ScreenToTile( mouseX, mouseY );
	if ( pos.q >= 0 && pos.q < tile_cols &&
		 pos.r >= 0 && pos.r < tile_rows ) {
	
		return &tiles[ pos.q * tile_rows + pos.r ];
	}

	return nullptr;
}