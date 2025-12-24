#pragma once
#include "NetworkManager.h"
#include "CharacterTestScene.h"
#include "GameLoopScene.h"
#include "SceneType.h"
#include "OnlineScene.h"
#include "TitleScene.h"
class SceneManager {
public:
	SceneType scene;
	TitleScene titleScene;
	void Update( );

	SceneManager( );
	void SceneChange( );
	void SetScene( SceneType newScene );
	SceneType GetScene( ) const;
	void TransScene( SceneType next );
	OnlineScene& GetOnlineScene() { return onlineScene; }

private:
	CharacterTestScene testScene;
	GameLoopScene gameLoopScene;
	OnlineScene onlineScene;
	bool isClicked( );
};



