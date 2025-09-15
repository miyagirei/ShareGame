#include "Dxlib.h"
#include "MapCreate.h"

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
    if (scene == map1) {
        DrawString(200, 200, "map1", GetColor(255, 255, 255));
        //if (isClicked()) scene = map2;
    }
    else if (scene == map2) {
        DrawString(200, 200, "map2", GetColor(255, 255, 255));
        //if (isClicked()) scene = map3;
    }
    else if (scene == map3) {
        DrawString(200, 200, "map3", GetColor(255, 255, 255));
        //if (isClicked()) scene = map1;
    }
}


