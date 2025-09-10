#pragma once
#include "TileUtility.h"

enum class TileAction {
	None,
	Heal,
	Damage
};

class Tile {
public:
	TilePosition tilePosition;
	double x = 0;
	double y = 0;
	TileAction action = TileAction::None;

	Tile( int q, int r, TileAction act = TileAction::None );

	void Draw( ) const;
	bool IsClicked( int mouseX, int mouseY ) const;
};

