#pragma once
#include "Character.h"
#include <vector>
#include "Camera.h"

class Player {
public :
	std::vector<Character*> controlledUnits;
	Character* selectedUnit = nullptr;

	void AddUnit( Character* unit );
	void Update( double deltaTime );
	void Draw(const Camera& camera) const;

	void OnLeftClick(int mouseX, int mouseY, const Camera& camera);
	void OnRightClick(int mouseX, int mouseY, const Camera& camera);
};

