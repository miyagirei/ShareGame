#include "Character.h"
#include <cmath>
#include "TileUtility.h"
#include "DxLib.h"

Character::Character( const std::string& name, int startQ, int startR )
	:name( name ),
	tilePosition { startQ,startR },
	moveSpeed(100.0),
	characterState(CharacterState::Idle)
{
	TileToScreen( tilePosition.q, tilePosition.r, positionX, positionY );
	targetX = positionX;
	targetY = positionY;
}

void Character::MoveToTile( const TilePosition& targetTile ) {
	tilePosition = targetTile;
	TileToScreen( targetTile.q, targetTile.r , targetX , targetY);
	characterState = CharacterState::Moving;
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

void Character::Draw( ) const { 
	int color = ( characterState == CharacterState::Idle ) ? GetColor( 0, 0, 255 ) : GetColor( 0, 255, 0 );
	DrawCircle( ( int )positionX, ( int )positionY, 20, color, TRUE );
}