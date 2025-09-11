#pragma once
#include "Board.h"
#include "Player.h"
#include "UIManager.h"

class CharacterTestScene {
public:
	CharacterTestScene( );
	void Run( );

private:
	Board board;
	Player player;
	UIManager uiManager;

	int mouseX = 0;
	int mouseY = 0;

	void ProcessInput( );
	void Update( double deltaTime );
	void Draw( );
};

