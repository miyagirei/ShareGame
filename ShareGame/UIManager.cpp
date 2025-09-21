#include "UIManager.h"
#include "Dxlib.h"

void UIManager::AddButton( Button button ) { 
	buttons.push_back( button );
	
}

void UIManager::Draw( Player& player, Board& board, int mouseX, int mouseY ) { 
	for ( auto button : buttons ) { 
		if ( button.canShow( ) ) { 
			DrawBox( button.x, button.y, button.x + button.w, button.y + button.h,
					 GetColor( 150, 150, 150 ), TRUE );
			DrawString( button.x + 10, button.y + 10, button.label.c_str(), GetColor( 0, 0, 0 ) );
		}
	}
}

void UIManager::OnLeftClick( int mouseX, int mouseY, Player& player ) { 
	for ( auto button : buttons ) { 
		if ( !IsMouseOverButton( mouseX, mouseY , button) )return;

		button.onClick( );
	}

}

bool UIManager::IsMouseOverButton( int mouseX, int mouseY, Button button )const {
	return mouseX >= button.x && mouseX <= button.x + button.w &&
		mouseY >= button.y && mouseY <= button.y + button.h;
}