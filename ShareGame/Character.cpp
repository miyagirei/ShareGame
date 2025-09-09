#include "Character.h"
#include <cmath>

Character::Character( const std::string& name, int tileQ, int tileR, double positionX, double positionY )
	:name( name ),
	tilePosition { tileQ,tileR },
	positionX( positionX ),
	positionY( positionY ),
	moveSpeed( 100.0 ),
	targetX( positionX ),
	targetY( positionY ),
	characterState( CharacterState::Idle ) {

}

void Character::MoveTo( double targetX, double targetY ) { 
	this->targetX = targetX;
	this->targetY = targetY;
	characterState = CharacterState::Moving;
}

void Character::MoveToTile( int tileQ, int tileR ) { 
	double screenX;
	double screenY;

	TileToScreen( tileQ, tileR, screenX, screenY );
	MoveTo( screenX, screenY );

	tilePosition.q = tileQ;
	tilePosition.r = tileR;
}

void Character::Update( double deltaTime ) { 
	if ( characterState == CharacterState::Moving ) {
		double diffX = targetX - positionX;
		double diffY = targetY - positionY;
		double distance = std::sqrt( diffX * diffX + diffY * diffY );

		if ( distance < 1.0f ) { 
			positionX = targetX;
			positionY = targetY;
			characterState = CharacterState::Idle;
		} else { 
			double velocityX = diffX / distance * moveSpeed * deltaTime;
			double velocityY = diffY / distance * moveSpeed * deltaTime;
			positionX += velocityX;
			positionY += velocityY;

		}
	}
}