#include "GameManager.h"

void GameManager::AddPlayer( Player* player, Character* unit) {
	players.push_back( player );
	
	if ( unit != nullptr ) { 
		allUnits.push_back( unit );
		player->controlledUnits.push_back( unit );
	}
}

void GameManager::AddUnit( Character* unit, Player* player ) { 
	allUnits.push_back( unit );

	if ( player != nullptr ) { 
		player->controlledUnits.push_back( unit );
	}
}

void GameManager::Update( double deltaTime ) { 
	bool allPlayerEndTurn = true;
	
	for ( auto player : players ) { 
		player->Update( deltaTime );

		if ( !player->endTurn )allPlayerEndTurn = false;
	}

	for ( auto unit : allUnits ) {
		unit->Update( deltaTime );
	}

	if ( allPlayerEndTurn ) { 
		currentTurn++;
		for ( auto player : players ) { 
			player->endTurn = false;
		}
	}

	if ( currentTurn >= maxTurn ) { 
		requestedScene = SceneType::map3;
	}
}

void GameManager::Draw( const Camera& camera ) const { 
	for ( auto unit : allUnits ) { 
		unit->Draw( camera, allUnits);
	}
}

void GameManager::OnLeftClick( int mouseX, int mouseY, const Camera& camera ) { 
	players[ localPlayerId ]->OnLeftClick( mouseX, mouseY, camera , allUnits);
}

void GameManager::OnRightClick( int mouseX, int mouseY, const Camera& camera, NetworkManager* network ) {
	if ( players[ localPlayerId ]->OnRightClick( mouseX, mouseY, camera ) ) { 
		TilePosition target = players[ localPlayerId ]->GetLastMoveTarget( );
		if ( network ) { 
			std::string msg = "MOVE " + players[ localPlayerId ]->GetSelectedUnit()->GetName() + " " + std::to_string( target.q ) + " " + std::to_string( target.r );
			network->Send( msg );
		}
	}
}

Player& GameManager::GetLocalPlayer( ) { 
	return *players[ localPlayerId ];
}

void GameManager::SwitchActivePlayer( ) { 
	localPlayerId = ( localPlayerId + 1 ) % players.size( );
}

std::optional<SceneType> GameManager::GetRequestedScene( ) const { 
	return requestedScene;
}

Character* GameManager::FindCharacterByName( std::string name ) { 
	for ( Character* unit : allUnits ) { 
		if ( unit && unit->GetName( ) == name ) { 
			return unit;
		}
	}

	return nullptr;
}

void GameManager::MoveCharacter( std::string name, int tileQ, int tileR ) {
	Character* unit = FindCharacterByName( name );
	if ( unit != nullptr ) {
		unit->MoveToTile( tileQ, tileR );
	}
}