#pragma once
#include <string>
#include "TileUtility.h"

enum class CharacterState {
	Idle,
	Moving,
	Acting
};

class Character {
public:
	std::string name;
	TilePosition tilePosition;
	double positionX = 0.0;
	double positionY = 0.0;

	double moveSpeed = 0.0;
	double targetX = 0.0;
	double targetY = 0.0;

	CharacterState characterState;

	int colorR = 0;
	int colorG = 0;
	int colorB = 255;

	Character( const std::string& name, int startQ, int startR );

	void MoveToTile( const TilePosition& targetTile );
	void Update( double deltaTime );
	void Draw( )const;
	void ChangeColor( int r, int g, int b );
	TilePosition GetTilePosition( ) const;
};

