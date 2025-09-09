#pragma once
#include <string>

enum class CharacterState {
	Idle,
	Moving,
	Acting
};

struct TilePos {
	int q = 0;
	int r = 0;
};

class Character {
public:
	std::string name;
	TilePos tilePos;
	double positionX = 0.0;
	double positionY = 0.0;

	double moveSpeed = 0.0;
	double targetX = 0.0;
	double targetY = 0.0;

	CharacterState characterState;

	Character( const std::string& name, int tileQ, int tileR, double positionX, double positionY );

	void MoveTo( double targetX, double targetY );

	void Update( double deltaTime );
};

