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
//-----追記箇所-----
#include "DebugUI.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	/*
	ChangeWindowMode( TRUE );
	if ( DxLib_Init( ) == -1 ) return -1;

	CharacterTestScene testScene;
	testScene.Run( );

	DxLib_End( );
	return 0;
	*/
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	DebugUI debug;
    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();

		debug.SummonDebug();

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}