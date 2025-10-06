// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include "SceneManager.h"

SceneManager sceneManager;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR cmdline, int ) {
	SetDoubleStartValidFlag( TRUE );//多重起動処理
	ChangeWindowMode( TRUE );
	SetAlwaysRunFlag( TRUE );
	if ( DxLib_Init( ) == -1 ) return -1;
	while ( ProcessMessage( ) == 0 ) { 
		//map.SceneChange( );
		sceneManager.SceneChange( );
	}

	DxLib_End( );
	return 0;

}