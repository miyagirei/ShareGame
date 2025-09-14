#include "Tile.h"
#include "HexagonUtility.h"
#include "Dxlib.h"

Tile::Tile( int q, int r, TileAction act )
	:tilePosition { q,r },
	action( act ) {
	TileToScreen( q, r, x, y );
}

void Tile::Draw(bool highlight) const {
    int radius = 28;
    unsigned int color = GetColor(200, 200, 200);

    DrawHexagon((int)x, (int)y, radius, color, true);

    if (action == TileAction::Heal) {
        DrawHexagon((int)x, (int)y, radius, GetColor(0, 255, 0), true);
    }
    else if (action == TileAction::Damage) {
        DrawHexagon((int)x, (int)y, radius, GetColor(255, 0, 0), true);
    }

    if (highlight) {
        DrawHexagon((int)x, (int)y, radius, GetColor(255, 255, 0), false);
    }
}

bool Tile::IsClicked( int mouseX, int mouseY )const {
	return mouseX >= x && mouseX <= x + TILE_WIDTH &&
		mouseY >= y && mouseY <= y + TILE_HEIGHT;
}