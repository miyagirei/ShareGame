// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include <vector>
#include "MapCreate.h"

MapCreate map;

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	
	ChangeWindowMode( TRUE );
	if ( DxLib_Init( ) == -1 ) return -1;

	while ( ProcessMessage( ) == 0 ) { 
		map.SceneChange( );
	}

	DxLib_End( );
	return 0;

}