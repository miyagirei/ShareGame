#include "UIManager.h"
#include "Dxlib.h"

void UIManager::Draw( Player& player, Board& board, int mouseX, int mouseY ) { 
	Character* selected = player.selectedUnit;
	if ( selected == nullptr ) return;
	if ( !player.CanOperableUnit( ) )return;

	const Tile* tile = board.GetTileAt( selected->positionX, selected->positionY );

	if ( tile != nullptr && tile->action != TileAction::None ) { 
		DrawBox( actionButtonX, actionButtonY, actionButtonX + actionButtonW, actionButtonY + actionButtonH,
				 GetColor( 150, 150, 150 ), TRUE );
		DrawString( actionButtonX + 10, actionButtonY + 10, "Action!", GetColor( 0, 0, 0 ) );
	}
}

void UIManager::OnLeftClick( int mouseX, int mouseY, Player& player ) { 
	if ( !IsMouseOverButton( mouseX, mouseY ) )return;

	Character* selected = player.selectedUnit;

	if ( selected != nullptr && player.CanOperableUnit() ) { 
		selected->ChangeColor( 255, 255, 0 );
	}
}

bool UIManager::IsMouseOverButton( int mouseX, int mouseY )const { 
	return mouseX >= actionButtonX && mouseX <= actionButtonX + actionButtonW &&
		mouseY >= actionButtonY && mouseY <= actionButtonY + actionButtonH;
}