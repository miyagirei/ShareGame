#include "Board.h"
#include "Camera.h"
#include "Tile.h"
#include "DxLib.h"
#include <algorithm>
#include "GeneralPurpose.h"

Board::Board( int width, int height ):
tile_cols(width),
tile_rows(height){ 
	for ( int q = 0; q < width; ++q ) { 
		for ( int r = 0; r < height; ++r ) { 
			int centerQ = width / 2;
			int centerR = height / 2;

			TileType type = TileType::NoEntry;
			if ( IsInsideHexArea(q,r,centerQ,centerR,3)) {
				type = TileType::Field;
			}

			Tile tile( q, r, TileAction::None , type );
			tiles.emplace_back( tile );
		}
	}

	tiles[ 12 ].action = TileAction::Heal;
	tiles[ 15 ].action = TileAction::Damage;
}

bool Board::IsInsideHexArea( int q, int r, int centerQ, int centerR, int radius ) {
	int x1, y1, z1;
	int x2, y2, z2;

	OffsetToCube( q, r, x1, y1, z1 );
	OffsetToCube( centerQ, centerR, x2, y2, z2 );

    int dist = Max3( std::abs(x1 - x2), std::abs(y1 - y2), std::abs(z1 - z2) );

	return dist <= radius;
}

inline void Board::OffsetToCube( int q, int r, int& x, int& y, int& z ) {
	x = q - ( r - ( r & 1 ) ) / 2;
	z = r;
	y = -x - z;
}

void Board::Draw( const Camera& camera ) const {
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY); 
	Position  target = camera.convertScreenToFieldPosition( mouseX, mouseY );
	bool isClicking = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	const Tile* targetTile = GetTileAt( target.x, target.y );

	for (auto& tile : tiles) {
		bool highlight = false;
		if ( targetTile != nullptr && targetTile == &tile) { 
			tile.Draw( camera,true);
		} else { 
			tile.Draw( camera,false );
		}
	}
}

const Tile* Board::GetTileAt( double mouseX, double mouseY )const {

	TilePosition pos = ScreenToTile( mouseX, mouseY );
	if ( pos.q >= 0 && pos.q < tile_cols &&
		 pos.r >= 0 && pos.r < tile_rows ) {
	
		return &tiles[ pos.q * tile_rows + pos.r ];
	}

	return nullptr;
}