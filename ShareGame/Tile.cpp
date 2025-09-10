#include "Tile.h"
#include "Dxlib.h"

Tile::Tile( int q, int r, TileAction act )
	:tilePosition { q,r },
	action( act ) {
	TileToScreen( q, r, x, y );
}

void Tile::Draw( ) const { 
	DrawBox( x - TILE_WIDTH / 4, y - TILE_HEIGHT / 4, x + TILE_WIDTH /4, y + TILE_HEIGHT / 4, GetColor( 200, 200, 200 ), FALSE );

	if ( action == TileAction::Heal ) { 
		DrawBox( x - TILE_WIDTH / 4, y - TILE_HEIGHT / 4,  x + TILE_WIDTH / 4,  y + TILE_HEIGHT / 4, GetColor( 0, 255, 0 ), TRUE );
	} else if ( action == TileAction::Damage ) {
		DrawBox( x - TILE_WIDTH / 4, y - TILE_HEIGHT / 4, x + TILE_WIDTH / 4, y + TILE_HEIGHT / 4, GetColor( 255, 0, 0 ), TRUE );
	}
}

bool Tile::IsClicked( int mouseX, int mouseY )const {
	return mouseX >= x && mouseX <= x + TILE_WIDTH &&
		mouseY >= y && mouseY <= y + TILE_HEIGHT;
}