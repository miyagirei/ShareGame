#include "Dxlib.h"
#include "MapCreate.h"
#include "DebugUI.h"

MapCreate::MapCreate( ) {
	scene = SceneType::map2;
}

bool MapCreate::isClicked() {
	static int prevMouse = 0;
	int mouseInput = GetMouseInput();

	bool clicked = ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT));

	prevMouse = mouseInput;
	return clicked;
}


void MapCreate::SceneChange() {
    DebugUI debug;
    switch ( scene ) {
    case SceneType::map1:
        testScene.Run( );
        break;

    case SceneType::map2:
        gameLoopScene.Run( );
        if ( auto next = gameLoopScene.game.GetRequestedScene( ) ) { 
            TransScene( *next );
        }
        break;

    case SceneType::map3:
        
        ClearDrawScreen( );
        debug.SummonDebug( );
        DrawString( 200, 200, "map3", GetColor( 255, 255, 255 ) );
        ScreenFlip( );
        break;
    }
}


void MapCreate::TransScene( SceneType next ) {
    scene = next;
}