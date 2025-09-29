#pragma once
#include "UIManager.h"
#include "NetworkManager.h"
class OnlineScene {
public:
	OnlineScene( );
	void Run( double deltaTime = 1.0 / 60.0 );

	NetworkManager network;
	UIManager uiManager;

private:
	bool initialize = false;

	void Initialize( );
};

