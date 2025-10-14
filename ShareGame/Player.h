#pragma once
#include "Character.h"
#include <vector>
#include "Camera.h"

enum class PlayerType {
	Human,
	AI,
	Remote,
};

class Player {
public :
	int playerId;
	PlayerType playerType;
	double money;

	std::vector<Character*> controlledUnits;
	Character* selectedUnit = nullptr;

	bool endTurn = false;
	TilePosition lastMoveTarget;

	Player( int id, PlayerType type );

	TilePosition GetLastMoveTarget( ) const;

	void AddUnit( Character* unit );
	void Update( double deltaTime );
	void Draw(const Camera& camera) const;

	void OnLeftClick( int mouseX, int mouseY, const Camera& camera, std::vector<Character*> units );
	bool OnRightClick(int mouseX, int mouseY, const Camera& camera);
	bool CanOperableUnit( );

	Character* GetSelectedUnit( )const;

private:
};

