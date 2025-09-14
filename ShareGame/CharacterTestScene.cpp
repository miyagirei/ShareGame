#include "CharacterTestScene.h"
#include "DxLib.h"
#include "MapCreate.h"

CharacterTestScene::CharacterTestScene( ):board(10,10)
{
	Character* unit1 = new Character( "Unit1",0,0 );
	Character* unit2 = new Character( "Unit2",2,1 );

	player.AddUnit( unit1 );
	player.AddUnit( unit2 );


}

void CharacterTestScene::Run( ) { 
	double deltaTime = 1.0 / 60.0;
		MapCreate test;
	while ( ProcessMessage() == 0 ) {
		GetMousePoint( &mouseX, &mouseY );

		ProcessInput( );
		Update( deltaTime );
		test.SceneChange( );
		ClearDrawScreen( );
		Draw( );
		ScreenFlip( );

	}
}

void CharacterTestScene::ProcessInput( ) { 
	if ( GetMouseInput() & MOUSE_INPUT_RIGHT ) { 
		const Tile* clickedTile = board.GetTileAt( mouseX, mouseY );
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


	board.Draw( );
	player.Draw( );

	uiManager.Draw( player, board, mouseX, mouseY );

	if ( player.selectedUnit != nullptr ) { 
		DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),
					  player.selectedUnit->name.c_str() );
		DrawFormatString( 10, 30, GetColor( 255, 255, 255 ),
						  "TileQ: %d", player.selectedUnit->GetTilePosition().q );
		DrawFormatString( 10, 50, GetColor( 255, 255, 255 ),
						  "TileR: %d", player.selectedUnit->GetTilePosition( ).r );	

	}


	    const Tile* tile = board.GetTileAt( mouseX, mouseY );
		if ( tile != nullptr ) {
			TilePosition targetTile = ScreenToTile( mouseX, mouseY );
			double tx, ty;
			TileToScreen( targetTile.q, targetTile.r, tx, ty );

			//DrawFormatString( 10, 70, GetColor( 255, 255, 255 ),
			//				  "MouseTileQ: %d", targetTile.q);
			//DrawFormatString( 10, 90, GetColor( 255, 255, 255 ),
			//				  "MouseTileR: %d", targetTile.r );
			//DrawFormatString( 10, 110, GetColor( 255, 255, 255 ),
			//				  "MouseTileX: %d", ( int )tx );
			//DrawFormatString( 10, 130, GetColor( 255, 255, 255 ),
			//				  "MouseTileY: %d", ( int )ty );
			DrawFormatString( 500, 10, GetColor( 255, 255, 255 ),
							  "MouseX: %d", mouseX );
			DrawFormatString( 500, 30, GetColor( 255, 255, 255 ),
							  "MouseY: %d", mouseY );
			//DrawFormatString( 10, 190, GetColor( 255, 255, 255 ),
			//				  "Action: %d", tile->action );
		}
}

