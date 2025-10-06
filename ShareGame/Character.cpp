#include "Character.h"
#include <cmath>
#include "TileUtility.h"
#include "DxLib.h"

Character::Character(const std::string& name, int startQ, int startR)
    : name(name),
    tilePosition{ startQ, startR },
    moveSpeed(100.0),
    characterState(CharacterState::Idle),
    colorR(0), colorG(0), colorB(255) {
    TileToScreen( tilePosition.q, tilePosition.r, positionX, positionY );
    targetX = positionX;
    targetY = positionY;
}

void Character::MoveToTile(const TilePosition& targetTile) {
    tilePosition = targetTile;
    TileToScreen( targetTile.q, targetTile.r, targetX, targetY );
    characterState = CharacterState::Moving;
}

void Character::MoveToTile( int targetQ, int targetR ) {
    tilePosition = { targetQ , targetR };
    TileToScreen( targetQ, targetR, targetX, targetY );
    characterState = CharacterState::Moving;
}

void Character::Update(double deltaTime) {
    if (characterState == CharacterState::Moving) {
        double diffX = targetX - positionX;
        double diffY = targetY - positionY;
        double distance = std::sqrt(diffX * diffX + diffY * diffY);

        if (distance < 1.0f) {
            positionX = targetX;
            positionY = targetY;
            characterState = CharacterState::Idle;
        }
        else {
            double velocityX = diffX / distance * moveSpeed * deltaTime;
            double velocityY = diffY / distance * moveSpeed * deltaTime;
            positionX += velocityX;
            positionY += velocityY;
        }
    }
}

void Character::Draw(const Camera& camera) const {
    int sx = camera.convertFieldPositionToScreenX(Position{ positionX, positionY });
    int sy = camera.convertFieldPositionToScreenY(Position{ positionX, positionY });
    int sr = camera.convertSizeToScreenSize(20);

    DrawCircle(sx, sy, sr, GetColor(colorR, colorG, colorB), TRUE);
}

void Character::ChangeColor(int r, int g, int b) {
    colorR = r;
    colorG = g;
    colorB = b;
}

TilePosition Character::GetTilePosition( ) const {
	return ScreenToTile( positionX, positionY );
}

std::string Character::GetName( )const { 
    return name;
}