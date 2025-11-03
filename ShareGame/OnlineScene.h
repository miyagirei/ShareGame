#pragma once
#include "UIManager.h"
#include "NetworkManager.h"
#include "GameLoopScene.h"
class OnlineScene {
public:
	OnlineScene( );
	void Run( double deltaTime = 1.0 / 60.0 );

	NetworkManager network;
	UIManager uiManager;

	void SetHost(bool host) { isHost = host; }
	bool IsHost() const { return isHost; }

private:
	bool initialize = false;
	bool isHost = true;
	GameLoopScene gameLoopScene;

	void Initialize( );
};

