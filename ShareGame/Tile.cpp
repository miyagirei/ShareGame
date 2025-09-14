#include "Tile.h"
#include "HexagonUtility.h"
#include "Dxlib.h"

Tile::Tile(int q, int r, TileAction act)
    : tilePosition{ q, r }, action(act)
{
   
}

void Tile::Draw(const Camera& camera) const {
    int radius = 28;

    double fieldX, fieldY;
    TileToScreen(tilePosition.q, tilePosition.r, fieldX, fieldY);

    int sx = camera.convertFieldPositionToScreenX(Position{ fieldX, fieldY });
    int sy = camera.convertFieldPositionToScreenY(Position{ fieldX, fieldY });
    int sr = camera.convertSizeToScreenSize(radius);

    unsigned int color = GetColor(200, 200, 200);
    DrawHexagon(sx, sy, sr, color, true);

    if (action == TileAction::Heal) {
        DrawHexagon(sx, sy, sr, GetColor(0, 255, 0), true);
    }
    else if (action == TileAction::Damage) {
        DrawHexagon(sx, sy, sr, GetColor(255, 0, 0), true);
    }
}

bool Tile::IsClicked( int mouseX, int mouseY )const {
	return mouseX >= x && mouseX <= x + TILE_WIDTH &&
		mouseY >= y && mouseY <= y + TILE_HEIGHT;
}