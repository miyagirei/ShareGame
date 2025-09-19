#include "Player.h"
#include "Dxlib.h"
#include "TileUtility.h"
#include "Camera.h"
#include "CharacterTestScene.h"

Player::Player( int id, PlayerType type ) :
playerId(id),
playerType(type){

}

void Player::AddUnit(Character* unit) {
    controlledUnits.push_back(unit);
}

void Player::Update(double deltaTime) {
    for (auto unit : controlledUnits) {
        unit->Update(deltaTime);
    }
}

///現在プレイヤーが所持しているユニットを表示する用
///CharacterTestScene->使用している//後から消す可能性あり
///GameLoopScene->未使用
void Player::Draw(const Camera& camera) const {
    for (auto unit : controlledUnits) {
        unit->Draw(camera);
    }
}


void Player::OnLeftClick(int mouseX, int mouseY, const Camera& camera , std::vector<Character*> units) {
    Position fieldPos = camera.convertScreenToFieldPosition(mouseX, mouseY);
    TilePosition clickedTile = ScreenToTile(fieldPos.x, fieldPos.y);

    for (auto unit : units) {
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
    if (selectedUnit && CanOperableUnit()) {
        Position fieldPos = camera.convertScreenToFieldPosition(mouseX, mouseY);
        TilePosition targetTile = ScreenToTile(fieldPos.x, fieldPos.y);

        selectedUnit->MoveToTile(targetTile);
    }
}

bool Player::CanOperableUnit( ) { 
    for ( auto unit : controlledUnits ) { 
        if ( selectedUnit == unit ) { 
            return true;
        }
    }

    return false;
}