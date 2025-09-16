#include "Dxlib.h"
#include "MapCreate.h"
#include "DebugUI.h"

MapCreate::MapCreate( ) {
	scene = mapNum::map1;
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
    case map1:
        testScene.Run( );
        break;

    case map2:
        ClearDrawScreen( );
        debug.SummonDebug( );
        DrawString( 200, 200, "map2", GetColor( 255, 255, 255 ) );
        ScreenFlip( );
        break;

    case map3:
        
        ClearDrawScreen( );
        debug.SummonDebug( );
        DrawString( 200, 200, "map3", GetColor( 255, 255, 255 ) );
        ScreenFlip( );
        break;
    }
}


