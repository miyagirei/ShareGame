#pragma once
#include <vector>
#include "Player.h"
#include <optional>
#include "SceneType.h"

struct PlayerState {
	int stamina;
	bool endedTurn;
};

class GameManager {
public:
	std::vector<Player*> players;
	std::vector<Character*> allUnits;
	int localPlayerId = 0;
	int currentTurn = 1;
	int maxTurn = 3;
	std::optional<SceneType> GetRequestedScene( ) const;

	void AddPlayer( Player* player, Character* unit = nullptr );
	void Update( double deltaTime );
	void Draw( const Camera& camera ) const;
	
	void OnLeftClick( int mouseX, int mouseY, const Camera& camera );
	void OnRightClick( int mouseX, int mouseY, const Camera& camera );

	Player& GetLocalPlayer( );
	void SwitchActivePlayer( );
private:
	std::optional<SceneType> requestedScene;
};

