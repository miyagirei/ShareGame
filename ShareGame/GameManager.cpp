#include "GameManager.h"

void GameManager::AddPlayer( Player* player, Character* unit) {
	players.push_back( player );
	
	if ( unit != nullptr ) { 
		allUnits.push_back( unit );
		player->controlledUnits.push_back( unit );
	}
}

void GameManager::Update( double deltaTime ) { 
	bool allPlayerEndTurn = true;
	
	for ( auto player : players ) { 
		player->Update( deltaTime );

		if ( !player->endTurn )allPlayerEndTurn = false;
	}

	if ( allPlayerEndTurn ) { 
		currentTurn++;
		for ( auto player : players ) { 
			player->endTurn = false;
		}
	}
}

void GameManager::Draw( const Camera& camera ) const { 
	for ( auto unit : allUnits ) { 
		unit->Draw( camera );
	}
}

void GameManager::OnLeftClick( int mouseX, int mouseY, const Camera& camera ) { 
	players[ localPlayerId ]->OnLeftClick( mouseX, mouseY, camera , allUnits);
}

void GameManager::OnRightClick( int mouseX, int mouseY, const Camera& camera ) { 
	players[ localPlayerId ]->OnRightClick( mouseX, mouseY, camera );
}

Player& GameManager::GetLocalPlayer( ) { 
	return *players[ localPlayerId ];
}

void GameManager::SwitchActivePlayer( ) { 
	localPlayerId = ( localPlayerId + 1 ) % players.size( );
}