#include "Player.h"
#include "Dxlib.h"
#include "TileUtility.h"

void Player::AddUnit( Character* unit ) { 
	controlledUnits.push_back( unit );
}

void Player::Update( double deltaTime ) { 
	for ( auto unit : controlledUnits ) { 
		unit->Update( deltaTime );
	}
}

void Player::Draw( )const { 
	for ( auto unit : controlledUnits ) { 
		unit->Draw( );
	}
}

void Player::OnLeftClick( int mouseX, int mouseY ) {
	for ( auto unit : controlledUnits ) { 
		TilePosition clickedTile = ScreenToTile( mouseX, mouseY );
		double unitX = 0.0;
		double unitY = 0.0;

		TileToScreen( unit->tilePosition.q, unit->tilePosition.r, unitX, unitY );

		double dx = mouseX - unitX;
		double dy = mouseY - unitY;

		if ( std::sqrt( dx * dx + dy * dy ) < 20.0 ) { 
			selectedUnit = unit;
			return;
		}
	}
	selectedUnit = nullptr;
}

void Player::OnRightClick( int mouseX, int mouseY ) { 
	if ( selectedUnit ) { 
		TilePosition targetTile = ScreenToTile( mouseX, mouseY );
		selectedUnit->MoveToTile( targetTile );
	}
}