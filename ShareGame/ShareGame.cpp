// ShareGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "ShareGame.h"
#include "Dxlib.h"
#include "Character.h"
#include "Player.h"
#include <vector>
#include "Board.h"
#include "CharacterTestScene.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	ChangeWindowMode( TRUE );

	if ( DxLib_Init( ) == -1 ) return -1;

	CharacterTestScene testScene;
	testScene.Run( );

	DxLib_End( );
	return 0;
}