#pragma once
#include "CharacterTestScene.h"

//‰¼
enum mapNum {
	map1, //init
	map2, //2
	map3 //3
};

class MapCreate {
public:
	MapCreate( );

	mapNum scene;
	void SceneChange( );

	void SetScene(mapNum newScene) { scene = newScene; }
	mapNum GetScene() const { return scene; }

private:
	CharacterTestScene testScene;
	bool isClicked( );
};