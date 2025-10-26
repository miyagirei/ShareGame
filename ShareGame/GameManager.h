#pragma once
#include <vector>
#include "Player.h"
#include <optional>
#include "SceneType.h"
#include "NetworkManager.h"

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
	void AddUnit( Character* unit ,Player* player = nullptr );
	void Update( double deltaTime );
	void Draw( const Camera& camera ) const;
	
	void OnLeftClick( int mouseX, int mouseY, const Camera& camera );
	void OnRightClick( int mouseX, int mouseY, const Camera& camera , NetworkManager* network = nullptr );

	Character* FindCharacterByName( std::string name);
	void MoveCharacter( std::string name , int tileQ, int tileR);

	Player& GetLocalPlayer( );
	void SwitchActivePlayer( );
private:
	std::optional<SceneType> requestedScene;
};

