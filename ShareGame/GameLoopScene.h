#pragma once
#include "Board.h"
#include "Player.h"
#include "UIManager.h"
#include "Camera.h"
#include "GameManager.h"
#include "NetworkManager.h"

class GameLoopScene {
public:
	GameLoopScene( NetworkManager* net = nullptr);
	void Run( double deltaTime = 1.0 / 60.0 , bool isHost = true);
	GameManager game;

private:
	bool initialize = false;

	Board board;
	UIManager uiManager;
	Camera camera;
	NetworkManager* network;

	int mouseX = 0;
	int mouseY = 0;

	void Initialize( bool isHost );
	void ProcessInput( );
	void Update( double deltaTime );
	void Draw( );

	void DebugSwitchActivePlayer( );
};

