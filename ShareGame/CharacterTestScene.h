#pragma once
#include "Board.h"
#include "Player.h"
#include "UIManager.h"
#include "Camera.h"

class CharacterTestScene {
public:
	CharacterTestScene( );
	void Run( double deltaTime = 1.0 / 60.0 );

private:
	Board board;
	Player player;
	UIManager uiManager;
	Camera camera;

	int mouseX = 0;
	int mouseY = 0;

	void ProcessInput( );
	void Update( double deltaTime );
	void Draw( );
};

