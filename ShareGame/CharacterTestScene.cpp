#include "CharacterTestScene.h"
#include "DxLib.h"
#include "MapCreate.h"
#include "Camera.h"
#include "DebugUI.h"

CharacterTestScene::CharacterTestScene( ) :board( 10, 10 ), camera( 0, 0 ) ,player(0 , PlayerType::Human){//playerはGameLoop作成時の蛇足なので必要に応じて消してください
	Character* unit1 = new Character( "Unit1", 0, 0 );
	Character* unit2 = new Character( "Unit2", 2, 1 );


	player.AddUnit( unit1 );
	player.AddUnit( unit2 );

	Button actionButton = { "action" ,
	[ & ] ( ) {
		Character* selected = player.selectedUnit;
		if ( selected != nullptr && player.CanOperableUnit( ) ) {
			selected->ChangeColor( 255, 255, 0 );
		}
	},
	[ & ] ( ) {
		if ( !player.CanOperableUnit( ) )return false;

		Character* selected = player.selectedUnit;
		if ( !selected ) return false;

		const Tile* tile = board.GetTileAt( selected->positionX, selected->positionY );
		if ( !tile ) return false;

		return tile->action != TileAction::None;
	},
		600,200,120,40
	};

	uiManager.AddButton( actionButton );
}

void CharacterTestScene::Run( double deltaTime ) {
	DebugUI debug;
		GetMousePoint( &mouseX, &mouseY );
		ProcessInput( );
		Update( deltaTime );
		ClearDrawScreen( );
		Draw( );
		debug.SummonDebug( );
		ScreenFlip( );
}

void CharacterTestScene::ProcessInput( ) {
	if ( GetMouseInput( ) & MOUSE_INPUT_RIGHT ) {
		const Tile* clickedTile = board.GetTileAt( mouseX, mouseY );
		if ( clickedTile != nullptr ) {
			player.OnRightClick( mouseX, mouseY, camera );
		}
	}

	if ( GetMouseInput( ) & MOUSE_INPUT_LEFT ) {
		uiManager.OnLeftClick( mouseX, mouseY, player );
		player.OnLeftClick( mouseX, mouseY, camera , player.controlledUnits);//GameManagerで全体のユニットを管理するようにしたため
		                                                                     //controlledUnitsで代用しています
	}
}

void CharacterTestScene::Update( double deltaTime ) {
	camera.updateByMouseWheel( );
	player.Update( deltaTime );
}

void CharacterTestScene::Draw( ) {


	board.Draw( camera );
	player.Draw( camera );

	uiManager.Draw( player, board, mouseX, mouseY );

	if ( player.selectedUnit != nullptr ) {
		DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),
						  player.selectedUnit->name.c_str( ) );
		DrawFormatString( 10, 30, GetColor( 255, 255, 255 ),
						  "TileQ: %d", player.selectedUnit->GetTilePosition( ).q );
		DrawFormatString( 10, 50, GetColor( 255, 255, 255 ),
						  "TileR: %d", player.selectedUnit->GetTilePosition( ).r );
		DrawFormatString( 10, 70, GetColor( 255, 255, 255 ),
						  "PosX: %d", ( int )player.selectedUnit->positionX );
		DrawFormatString( 10, 90, GetColor( 255, 255, 255 ),
						  "PosY: %d", ( int )player.selectedUnit->positionY );

	}

	Position world_pos = camera.convertScreenToFieldPosition( mouseX, mouseY );

	const Tile* tile = board.GetTileAt( world_pos.x, world_pos.y );
	if ( tile != nullptr ) {
		TilePosition targetTile = ScreenToTile( world_pos.x, world_pos.y );
		double tx, ty;
		TileToScreen( targetTile.q, targetTile.r, tx, ty );

		DrawFormatString( 500, 90, GetColor( 255, 255, 255 ),
						  "MouseTileQ: %d", targetTile.q );
		DrawFormatString( 500, 110, GetColor( 255, 255, 255 ),
						  "MouseTileR: %d", targetTile.r );
		//DrawFormatString( 10, 110, GetColor( 255, 255, 255 ),
		//				  "MouseTileX: %d", ( int )tx );
		//DrawFormatString( 10, 130, GetColor( 255, 255, 255 ),
		//				  "MouseTileY: %d", ( int )ty );
		//DrawFormatString( 10, 190, GetColor( 255, 255, 255 ),
		//				  "Action: %d", tile->action );
	}
	DrawFormatString( 500, 10, GetColor( 255, 255, 255 ),
					  "MouseX: %d", mouseX );
	DrawFormatString( 500, 30, GetColor( 255, 255, 255 ),
					  "MouseY: %d", mouseY );
	DrawFormatString( 500, 50, GetColor( 255, 255, 255 ),
					  "CameraX: %d", ( int )world_pos.x );
	DrawFormatString( 500, 70, GetColor( 255, 255, 255 ),
					  "CameraY: %d", ( int )world_pos.y );
}

