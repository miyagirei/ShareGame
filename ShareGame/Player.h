#pragma once
#include "Character.h"
#include <vector>

class Player {
public :
	std::vector<Character*> controlledUnits;
	Character* selectedUnit = nullptr;

	void AddUnit( Character* unit );
	void Update( double deltaTime );
	void Draw( ) const;

	void OnLeftClick( int mouseX, int mouseY );
	void OnRightClick( int mouseX, int mouseY );
};

