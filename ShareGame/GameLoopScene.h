#pragma once
#include "Board.h"
#include "Player.h"
#include "UIManager.h"
#include "Camera.h"
#include "GameManager.h"

class GameLoopScene {
public:
	GameLoopScene( NetworkManager* net = nullptr);
	void Run( double deltaTime = 1.0 / 60.0 , bool isHost = true);
	GameManager game;

private:
	//Player* player1;

	Board board;
	UIManager uiManager;
	Camera camera;

	int mouseX = 0;
	int mouseY = 0;

	void ProcessInput( );
	void Update( double deltaTime );
	void Draw( );

	void DebugSwitchActivePlayer( );
};

