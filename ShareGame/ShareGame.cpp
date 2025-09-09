// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include "Character.h"
#include <vector>

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	ChangeWindowMode( TRUE );

	if ( DxLib_Init( ) == -1 ) return -1;

	Character player( "Test", 0, 0, 320.0, 240.0 );

	std::vector<TilePosition> tiles;

	for ( int q = 0; q < 10; q++ ) {
		for ( int r = 0; r < 10; r++ ) { 
			tiles.push_back( { q,r } );
		}
	}

	double deltaTile = 1.0 / 60.0;
	bool prevUpKey = false;
	while ( ProcessMessage( ) == 0 ) {
		ClearDrawScreen( );

		bool currentUpKey = CheckHitKey( KEY_INPUT_UP ) != 0;
		for ( auto& t : tiles ) {
			double x, y;
			TileToScreen( t.q, t.r, x, y );
			DrawBox( int( x ), int( y ), int( x + 50 ), int( y + 50 ), GetColor( 200, 200, 200 ), FALSE );
		}
		
		if ( CheckHitKey( KEY_INPUT_RIGHT ) ) player.MoveToTile( player.tilePosition.q + 1, player.tilePosition.r );
		if ( CheckHitKey( KEY_INPUT_LEFT ) )  player.MoveToTile( player.tilePosition.q - 1, player.tilePosition.r );
		if ( CheckHitKey( KEY_INPUT_DOWN ) )  player.MoveToTile( player.tilePosition.q, player.tilePosition.r + 1 );
		
		if ( currentUpKey && !prevUpKey )    player.MoveToTile( player.tilePosition.q, player.tilePosition.r - 1 );

		prevUpKey = currentUpKey;
		DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),
						  "Tile Q: %d, Tile R: %d\nPos X: %.1f, Pos Y: %.1f",
						  player.tilePosition.q, player.tilePosition.r,
						  player.positionX, player.positionY );

		player.Update( deltaTile );

		DrawCircle( player.positionX, player.positionY, 20, GetColor( 255, 0, 0 ), TRUE );
	
		ScreenFlip( );
	}

	DxLib_End( );
	return 0;
}