// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include "Character.h"
#include "Player.h"
#include <vector>

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	ChangeWindowMode( TRUE );

	if ( DxLib_Init( ) == -1 ) return -1;

	Player player;
	Character unit1( "Unit1", 0, 0 );
	Character unit2( "Unit2", 2, 1 );

	player.AddUnit( &unit1 );
	player.AddUnit( &unit2 );

	int mouseX;
	int mouseY;

	std::vector<TilePosition> tiles;

	for ( int q = 0; q < 10; q++ ) {
		for ( int r = 0; r < 10; r++ ) { 
			tiles.push_back( { q,r } );
		}
	}

	double deltaTile = 1.0 / 60.0;
	while ( ProcessMessage( ) == 0 ) {

		GetMousePoint( &mouseX, &mouseY );
		if ( GetMouseInput( ) & MOUSE_INPUT_LEFT ) {
			player.OnLeftClick( mouseX, mouseY );
		}
		if ( GetMouseInput( ) & MOUSE_INPUT_RIGHT ) {
			player.OnRightClick( mouseX, mouseY );
		}

		player.Update( deltaTile );

		ClearDrawScreen( );
		DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),
						  "SelectUnit: %d",
						  player.selectedUnit );
		for ( auto& t : tiles ) {
			double x, y;
			TileToScreen( t.q, t.r, x, y );
			DrawBox( int( x -25), int( y-25 ), int( x + 25 ), int( y + 25 ), GetColor( 200, 200, 200 ), FALSE );
		}
		player.Draw( );
		ScreenFlip( );
	}

	DxLib_End( );
	return 0;
}