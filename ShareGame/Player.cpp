#include "Player.h"
#include "Dxlib.h"
#include "TileUtility.h"
#include "Camera.h"
#include "CharacterTestScene.h"

void Player::AddUnit(Character* unit) {
    controlledUnits.push_back(unit);
}

void Player::Update(double deltaTime) {
    for (auto unit : controlledUnits) {
        unit->Update(deltaTime);
    }
}

void Player::Draw(const Camera& camera) const {
    for (auto unit : controlledUnits) {
        unit->Draw(camera);
    }
}


void Player::OnLeftClick(int mouseX, int mouseY, const Camera& camera) {
    Position fieldPos = camera.convertScreenToFieldPosition(mouseX, mouseY);
    TilePosition clickedTile = ScreenToTile(fieldPos.x, fieldPos.y);

    for (auto unit : controlledUnits) {
        double unitX = 0.0;
        double unitY = 0.0;
        TileToScreen(unit->tilePosition.q, unit->tilePosition.r, unitX, unitY);

        double dx = fieldPos.x - unitX;
        double dy = fieldPos.y - unitY;

        if (std::sqrt(dx * dx + dy * dy) < 20.0) {
            selectedUnit = unit;
            return;
        }
    }
    selectedUnit = nullptr;
}

void Player::OnRightClick(int mouseX, int mouseY, const Camera& camera) {
    if (selectedUnit) {
        Position fieldPos = camera.convertScreenToFieldPosition(mouseX, mouseY);
        TilePosition targetTile = ScreenToTile(fieldPos.x, fieldPos.y);

        selectedUnit->MoveToTile(targetTile);
    }
}