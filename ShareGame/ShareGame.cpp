// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include "Character.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	ChangeWindowMode( TRUE );

	if ( DxLib_Init( ) == -1 ) return -1;

	Character player( "Test", 0, 0, 320.0, 240.0 );
	player.MoveTo( 0.0, 0.0 );

	while ( ProcessMessage( ) == 0 ) {
		player.Update( 1.0 / 60.0 );
		ClearDrawScreen( );

		DrawCircle( player.positionX, player.positionY, 20, GetColor( 255, 0, 0 ), TRUE );
	
		ScreenFlip( );
	}

	DxLib_End( );
	return 0;
}