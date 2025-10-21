#include "Character.h"
#include <cmath>
#include "TileUtility.h"
#include "DxLib.h"

const int CHARACTER_SIZE = 30;

Character::Character( const std::string& name, int startQ, int startR )
	: name( name ),
	tilePosition { startQ, startR },
	moveSpeed( 100.0 ),
	characterState( CharacterState::Idle ),
	colorR( 0 ), colorG( 0 ), colorB( 255 ) {
	TileToScreen( tilePosition.q, tilePosition.r, positionX, positionY );
	targetX = positionX;
	targetY = positionY;
	image = LoadGraph( "image/pictgram_normal.png" );
	CreateMaskFromImage( "image/pictgram_normal.png" );
}

void Character::MoveToTile( const TilePosition& targetTile ) {
	tilePosition = targetTile;
	TileToScreen( targetTile.q, targetTile.r, targetX, targetY );
	characterState = CharacterState::Moving;
}

void Character::MoveToTile( int targetQ, int targetR ) {
	tilePosition = { targetQ , targetR };
	TileToScreen( targetQ, targetR, targetX, targetY );
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

void Character::Draw( const Camera& camera ) const {
	int sx = camera.convertFieldPositionToScreenX( Position { positionX, positionY } );
	int sy = camera.convertFieldPositionToScreenY( Position { positionX, positionY } );
	int sr = camera.convertSizeToScreenSize( CHARACTER_SIZE );

	DrawExtendGraph( sx - sr / 2, sy - sr / 2, sx + sr / 2, sy + sr / 2, image, TRUE );
	//DrawCircle(sx, sy, sr, GetColor(colorR, colorG, colorB), TRUE);
}

void Character::ChangeColor( int r, int g, int b ) {
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

void Character::CreateMaskFromImage( const char* filename ) {
	int softImage = LoadSoftImage( filename );

	if ( softImage == -1 ) {
		return;
	}

	int w, h;
	GetSoftImageSize( softImage, &w, &h );
	mask.resize( h, std::vector < bool >( w, false ) );

	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			int r, g, b, a;
			GetPixelSoftImage( softImage, x, y, &r, &g, &b, &a );
			if ( a > 128 ) mask[ y ][ x ] = true;
		}
	}

	DeleteSoftImage( softImage );
}

bool Character::IsClick( int mouseX, int mouseY, const Camera& camera ) {
	if ( mask.empty( ) ) return false;

	int sx = camera.convertFieldPositionToScreenX( Position { positionX, positionY } );
	int sy = camera.convertFieldPositionToScreenY( Position { positionX, positionY } );
	int sr = camera.convertSizeToScreenSize( CHARACTER_SIZE );

	int w, h;
	GetGraphSize( image, &w, &h );

	int drawW = sr;
	int drawH = sr;

	float startX = sx - drawW / 2.0f;
	float startY = sy - drawH / 2.0f;

	float relX = ( mouseX - startX ) / drawW * w;
	float relY = ( mouseY - startY ) / drawH * h;

	int ix = static_cast< int >( relX );
	int iy = static_cast< int >( relY );

	if ( ix < 0 || iy < 0 || ix >= w || iy >= h ) return false;
	return mask[ iy ][ ix ];
}

void Character::DrawMaskDebug( const Camera& camera ) const {
	if ( mask.empty( ) ) return;

	int sx = camera.convertFieldPositionToScreenX( Position { positionX, positionY } );
	int sy = camera.convertFieldPositionToScreenY( Position { positionX, positionY } );
	int sr = camera.convertSizeToScreenSize( CHARACTER_SIZE );

	int w, h;
	GetGraphSize( image, &w, &h );

	int drawW = sr;
	int drawH = sr;

	float startX = sx - drawW / 2.0f;
	float startY = sy - drawH / 2.0f;

	for ( int y = 0; y < h; ++y ) {
		for ( int x = 0; x < w; ++x ) {
			if ( !mask[ y ][ x ] ) continue;

			float px = startX + ( x / ( float )w ) * drawW;
			float py = startY + ( y / ( float )h ) * drawH;

			DrawPixel( px, py, GetColor( 255, 0, 0 ) );
		}
	}
}