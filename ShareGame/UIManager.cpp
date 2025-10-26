#include "UIManager.h"
#include "Dxlib.h"

void UIManager::AddButton( Button button ) { 
	buttons.push_back( button );
	
}

void UIManager::AddText( Text text ) {
	texts.push_back( text );
}

void UIManager::Draw( Player& player, Board& board, int mouseX, int mouseY ) { 
	for ( auto button : buttons ) { 
		if ( button.canShow( ) ) { 
			int drawX = button.x;
			int drawY = button.y;

			switch ( button.anchor ) {
			case AnchorType::Center:
				drawX = button.x - button.w / 2;
				drawY = button.y - button.h / 2;
				break;
			case AnchorType::TopLeft:
				break;

			}
			int textX = drawX + ( button.w - GetDrawStringWidth( button.label.c_str( ), (int)button.label.size() ) ) / 2;
			int textY = drawY + ( button.h - 16 ) / 2;

			DrawBox( drawX, drawY, drawX + button.w, drawY + button.h,
					 GetColor( 150, 150, 150 ), TRUE );
			DrawString( textX, textY, button.label.c_str(), GetColor( 0, 0, 0 ) );
		}
	}

	for ( auto text : texts ) { 
		if ( text.canShow( ) ) { 
			std::string rendered = ReplaceVariables( text.label, text.variables );

			int drawX = text.x;
			int drawY = text.y;

			switch ( text.anchor ) {
			case AnchorType::Center:
				drawX = text.x - text.w / 2;
				drawY = text.y - text.h / 2;
				break;
			case AnchorType::TopLeft:
				break;

			}
			int textX = drawX + ( text.w - GetDrawStringWidth( rendered.c_str( ), ( int )rendered.size( ) ) ) / 2;
			int textY = drawY + ( text.h - 16 ) / 2;
			DrawString( textX, textY, rendered.c_str( ), GetColor( 0, 0, 0 ) );
		}
	}
}

void UIManager::OnLeftClick( int mouseX, int mouseY, Player& player ) { 
	lastUIClicked = false;
	for ( auto& button : buttons ) { 
		if (!button.canShow()) continue;
		if ( !IsMouseOverButton( mouseX, mouseY , button) )continue;

		button.onClick( );
		lastUIClicked = true;
		return;
	}

}

bool UIManager::IsMouseOverButton( int mouseX, int mouseY, Button button )const {
	return mouseX >= button.x && mouseX <= button.x + button.w &&
		mouseY >= button.y && mouseY <= button.y + button.h;
}

std::string UIManager::ReplaceVariables( const std::string& src,
							  const std::unordered_map<std::string, std::function<std::string( )>>& vars ) { 
	std::string result = src;
	for ( auto& [key, func] : vars ) { 
		std::string placeHolder = "{" + key + "}";
		size_t pos = result.find( placeHolder );
		if ( pos != std::string::npos ) { 
			result.replace( pos, placeHolder.size( ), func( ) );
		}
	}

	return result;
}