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

	std::vector<Character*> controlledUnits;
	Character* selectedUnit = nullptr;

	bool endTurn = false;

	Player( int id, PlayerType type );

	void AddUnit( Character* unit );
	void Update( double deltaTime );
	void Draw(const Camera& camera) const;

	void OnLeftClick( int mouseX, int mouseY, const Camera& camera, std::vector<Character*> units );
	void OnRightClick(int mouseX, int mouseY, const Camera& camera);
	bool CanOperableUnit( );

private:
};

