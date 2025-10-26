#pragma once
#include "TileUtility.h"
#include "Camera.h"

enum class TileAction {
	None,
	Heal,
	Damage
};

enum class TileType {
	Field,
	NoEntry
};

class Tile {
public:
	TilePosition tilePosition;
	double x = 0;
	double y = 0;
	TileAction action = TileAction::None;
	TileType type = TileType::NoEntry;

	Tile( int q, int r, TileAction act = TileAction::None , TileType type = TileType::NoEntry);

	void Draw( const Camera& camera,bool highlight ) const;
	bool IsClicked( double mouseX, double mouseY ) const;
	TileType GetTileType( ) const;
};

