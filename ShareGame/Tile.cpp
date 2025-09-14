#include "Tile.h"
#include "HexagonUtility.h"
#include "Dxlib.h"

//void Tile::Draw(const Camera& camera) const {

double PI = 3.14159265358979323846;

Tile::Tile( int q, int r, TileAction act )
	:tilePosition { q,r },
	action( act ) {
	TileToScreen( q, r, x, y );
}

void Tile::Draw(bool highlight) const {
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

    if (highlight) {
        DrawHexagon((int)x, (int)y, radius, GetColor(255, 255, 0), false);
    }
}

bool Tile::IsClicked( double mouseX, double mouseY )const {
    const int VERTS = 6;
    double vx[ VERTS ];
    double vy[ VERTS ];

    for ( int i = 0; i < VERTS; i++ ) { 
        double angle = PI / 3.0 * i + PI / 6.0;
        vx[ i ] = (int)x + HEX_RADIUS * std::cos( angle );
        vy[ i ] = (int)y + HEX_RADIUS * std::sin( angle );
    }

    bool inside = true;
    for ( int i = 0; i < VERTS; i++ ) { 
        int j = ( i + 1 ) & VERTS;
        double cross = ( vx[ j ] - vx[ i ] ) * ( mouseY - vy[ i ] ) - ( vy[ j ] - vy[ i ] ) * ( mouseX - vx[ i ] );
        if ( cross < 0.0 ) { 
            inside = false;
            break;
        }
    }

    return inside;
}