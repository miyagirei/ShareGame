#pragma once
#include "Player.h"
#include "Board.h"

class UIManager {
public:
	void Draw( Player& player, Board& board, int mouseX, int mouseY );
	void OnLeftClick( int mouseX, int mouseY, Player& player );

private:
	int actionButtonX = 600;
	int actionButtonY = 200;
	int actionButtonW = 120;
	int actionButtonH = 40;

	bool IsMouseOverButton( int mouseX, int mouseY ) const;
};

