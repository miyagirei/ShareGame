#include "Dxlib.h"
#include "MapCreate.h"

mapNum mapState = map1;

MapCreate::MapCreate( ) {
	scene = mapNum::map1;
}

bool MapCreate::isClicked() {
	static int prevMouse = 0;
	int mouseInput = GetMouseInput();

	bool clicked = ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouse & MOUSE_INPUT_LEFT));
	if(clicked) DrawString(100, 100, "clicked", GetColor(255, 255, 255));

	prevMouse = mouseInput;
	return clicked;
}

void MapCreate::SceneChange() {

	if (mapState == map1) {
		DrawFormatString(50, 50, GetColor(255, 255, 255), "aaa");
		DrawString(200, 200, "map1", GetColor(255, 255, 255));
		if (isClicked()) {
			mapState = map2;
		}
	}

	else if (mapState == map2) {
		DrawFormatString(50, 50, GetColor(255, 255, 255), "bbb");
		DrawString(200, 200, "map2", GetColor(255, 255, 255));
		if (isClicked()) {
			mapState = map3;
		}
	}

	else if (mapState == map3) {
		DrawFormatString(50, 50, GetColor(255, 255, 255), "ccc");
		DrawString(200, 200, "map3", GetColor(255, 255, 255));
		if (isClicked()) {
			mapState = map1;
		}
	}
}


