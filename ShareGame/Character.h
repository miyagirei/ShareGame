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

	Character( const std::string& name, int tileQ, int tileR, double positionX, double positionY );

	void MoveTo( double targetX, double targetY );
	void MoveToTile( int tileQ, int tileR );
	void Update( double deltaTime );
};

