#include "CharacterTestScene.h"
#include "DxLib.h"

CharacterTestScene::CharacterTestScene( ):board(10,10)
{
	Character* unit1 = new Character( "Unit1",0,0 );
	Character* unit2 = new Character( "Unit2",2,1 );

	player.AddUnit( unit1 );
	player.AddUnit( unit2 );


}

void CharacterTestScene::Run( ) { 
	double deltaTime = 1.0 / 60.0;
	while ( ProcessMessage() == 0 ) {
		GetMousePoint( &mouseX, &mouseY );

		ProcessInput( );
		Update( deltaTime );

		ClearDrawScreen( );
		Draw( );
		ScreenFlip( );

	}
}

void CharacterTestScene::ProcessInput( ) { 
	if ( GetMouseInput() & MOUSE_INPUT_RIGHT ) { 
		Tile* clickedTile = board.GetTileAt( mouseX, mouseY );
		if ( clickedTile != nullptr ) { 
			player.OnRightClick( mouseX, mouseY );
		}
	}	
	
	if ( GetMouseInput( ) & MOUSE_INPUT_LEFT ) {
		uiManager.OnLeftClick( mouseX, mouseY, player );
		player.OnLeftClick( mouseX, mouseY );
	}
}

void CharacterTestScene::Update( double deltaTime ) { 
	player.Update( deltaTime );
}

void CharacterTestScene::Draw( ) { 

	if ( player.selectedUnit != nullptr ) { 
	DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),
					  player.selectedUnit->name.c_str() );
		DrawFormatString( 10, 30, GetColor( 255, 255, 255 ),
						  "TileQ: %d", player.selectedUnit->GetTilePosition().q );
		DrawFormatString( 10, 50, GetColor( 255, 255, 255 ),
						  "TileR: %d", player.selectedUnit->GetTilePosition( ).r );	
	}

	board.Draw( );
	player.Draw( );

	uiManager.Draw( player, board, mouseX, mouseY );
}

