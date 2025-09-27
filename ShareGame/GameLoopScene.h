#pragma once
#include "Board.h"
#include "Player.h"
#include "UIManager.h"
#include "Camera.h"
#include "GameManager.h"

class GameLoopScene {
public:
	GameLoopScene( );
	void Run( double deltaTime = 1.0 / 60.0 );
	GameManager game;

private:
	//Player* player1;

	Board board;
	UIManager uiManager;
	Camera camera;

	int mouseX = 0;
	int mouseY = 0;

	bool showUnitInfo = false;

	void ProcessInput( );
	void Update( double deltaTime );
	void Draw( );

	void DebugSwitchActivePlayer( );
};

