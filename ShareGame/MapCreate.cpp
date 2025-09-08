#include "Dxlib.h"
#include "MapCreate.h"

mapNum map = map1;

void SceneChange() {
	if (map == map1) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "aaa");
	}

	else if (map == map2) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "bbb");
	}

	else if (map == map3) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "ccc");
	}
}