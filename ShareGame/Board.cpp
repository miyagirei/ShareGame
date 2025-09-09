#include "Board.h"

Board::Board( int width, int height ) { 
	for ( int q = 0; q < width; q++ ) { 
		for ( int r = 0; r < height; r++ ) { 
			tiles.emplace_back( q, r, TileAction::None );
		}
	}

	tiles[ 2 ].action = TileAction::Heal;
	tiles[ 5 ].action = TileAction::Damage;
}

void Board::Draw( ) const { 
	for ( const auto& tile : tiles ) { 
		tile.Draw( );
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