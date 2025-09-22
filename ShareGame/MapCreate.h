#pragma once
#include "CharacterTestScene.h"
#include "GameLoopScene.h"
#include "SceneType.h"

class MapCreate {
public:

	MapCreate( );

	SceneType scene;
	void SceneChange( );

	void SetScene( SceneType newScene) { scene = newScene; }
	SceneType GetScene() const { return scene; }
	void TransScene( SceneType next );

private:
	CharacterTestScene testScene;
	GameLoopScene gameLoopScene;
	bool isClicked( );
};