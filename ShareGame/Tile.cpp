#include "Tile.h"
#include "HexagonUtility.h"
#include "Dxlib.h"

double PI = 3.14159265358979323846;

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