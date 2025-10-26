#pragma once
#include <string>
#include "TileUtility.h"
#include "Camera.h"
#include <vector>
#include "GeneralPurpose.h"

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

	int image = -1;
	std::vector < std::vector<bool> >mask;

	Character( const std::string& name, int startQ, int startR );

	void MoveToTile( const TilePosition& targetTile );
	void MoveToTile( int targetQ , int targetR);
	void Update( double deltaTime );
	void Draw(const Camera& camera , const std::vector<Character*>& allCharacters)const;
	void ChangeColor( int r, int g, int b );
	TilePosition GetTilePosition( ) const;
	std::string GetName( )const;
	bool IsClick( int mouseX, int mouseY, const Camera& camera, const std::vector<Character*>& allCharacters );

	void DrawMaskDebug( const Camera& camera, const std::vector<Character*>& allCharacters ) const;
private:
	void CreateMaskFromImage( const char* filename );
	std::vector<const Character*> GetSameTileCharacters(const std::vector<Character*>& allCharacters) const ;
	int GetIndexInSameTile( const std::vector<const Character*>& sameTileCharacters ) const;
};

