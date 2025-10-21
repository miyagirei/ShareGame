#include "GameLoopScene.h"
#include "DxLib.h"
#include "Camera.h"
#include "InputManager.h"
#include <sstream>


GameLoopScene::GameLoopScene( NetworkManager* net )
	:board( 10, 10 ), camera( 0, 0 ), network( net ) {
}


void GameLoopScene::Initialize( bool isHost ) {
	Character* unit1 = new Character( "Unit1", 0, 0 );
	Character* unit2 = new Character( "Unit2", 2, 1 );

	Player* player1 = new Player( 0, PlayerType::Human );
	Player* player2 = new Player( 1, PlayerType::Human );

	game.AddPlayer( player1, unit1 );
	game.AddPlayer( player2, unit2 );

	if ( isHost ) {
		game.localPlayerId = 0;
	} else {
		game.localPlayerId = 1;
	}

	//テスト用のアクションを実行するためのボタン//現在はキャラクターの色が変わる
	Button actionButton = { "action" ,
	[ & ] ( ) {
		game.GetLocalPlayer( ).money += 1;
		//Character* selected = game.GetLocalPlayer( ).selectedUnit;
		//if ( selected != nullptr && game.GetLocalPlayer( ).CanOperableUnit( ) ) {
		//	selected->ChangeColor( 255, 255, 0 );
		//}
	},
	[ & ] ( ) {
		if ( !game.GetLocalPlayer( ).CanOperableUnit( ) )return false;

		Character* selected = game.GetLocalPlayer( ).selectedUnit;
		if ( !selected ) return false;

		const Tile* tile = board.GetTileAt( selected->positionX, selected->positionY );
		if ( !tile ) return false;

		return tile->action != TileAction::None;
	},
		500,200,120,40,AnchorType::TopLeft
	};

	Button nextTurnButton = { "NextTurn",
	[ & ] ( ) {
		game.GetLocalPlayer( ).endTurn = !game.GetLocalPlayer( ).endTurn;

	},
	[ ] ( ) {
		return true;
	},
		520,300,100,40,AnchorType::TopLeft
	};


	Button unitInfoButton = { "UnitInfo",
		[ & ] ( ) {
			showUnitInfo = !showUnitInfo;
		},

		[ & ] ( ) {
			return game.GetLocalPlayer( ).selectedUnit != nullptr;
		},

		0,0,100,30
	};

	uiManager.AddButton( actionButton );
	uiManager.AddButton( nextTurnButton );
	uiManager.AddButton( unitInfoButton );

	Text moneyText = { "お金: {money}",
		{
			{"money" , [ & ] ( ) { return std::to_string( ( int )game.GetLocalPlayer( ).money ); }}
		},
		[ & ] ( ) {
			return true;
		},
		320,10,150,30,AnchorType::Center
	};
	uiManager.AddText( moneyText );

	initialize = true;

	if ( network ) {
		network->onReceiveCallback = [ this ] ( const std::string& msg ) {
			std::istringstream iss( msg );
			std::string command, name;
			int q, r;
			iss >> command >> name >> q >> r;

			if ( command == "MOVE" ) {
				game.MoveCharacter( name, q, r );
			}

		};
	}
}

void GameLoopScene::Run( double deltaTime, bool isHost ) {
	if ( !initialize ) {
		Initialize( isHost );
	}
	GetMousePoint( &mouseX, &mouseY );
	ProcessInput( );
	Update( deltaTime );
	Draw( );
}

void GameLoopScene::ProcessInput( ) {
	InputManager::Update( );

	if ( InputManager::GetMouse( MOUSE_INPUT_RIGHT ) ) {
		Position world_pos = camera.convertScreenToFieldPosition( mouseX, mouseY );
		const Tile* clickedTile = board.GetTileAt( world_pos.x, world_pos.y );
		if ( clickedTile != nullptr ) {
			if ( clickedTile->GetTileType( ) == TileType::Field ) { 
				if ( network ) {
					game.OnRightClick( mouseX, mouseY, camera, network );
				} else {
					game.OnRightClick( mouseX, mouseY, camera );
				}
			}
		}
	}

	if ( InputManager::GetMouseDown( MOUSE_INPUT_LEFT ) ) {
		uiManager.OnLeftClick( mouseX, mouseY, game.GetLocalPlayer( ) );
		if ( !uiManager.WasUIClicked( ) ) {
			game.OnLeftClick( mouseX, mouseY, camera );
		}
	}

}

void GameLoopScene::Update( double deltaTime ) {
	camera.Update( mouseX, mouseY );
	game.Update( deltaTime );
	DebugSwitchActivePlayer( );
}

void GameLoopScene::Draw( ) {

	board.Draw( camera );
	game.Draw( camera );

	uiManager.Draw( game.GetLocalPlayer( ), board, mouseX, mouseY );

	if ( game.GetLocalPlayer( ).selectedUnit != nullptr ) {

		//game.GetLocalPlayer( ).selectedUnit->DrawMaskDebug( camera );//
		if ( showUnitInfo ) {
			DrawBox( 0, 30, 100, 150, GetColor( 128, 128, 128 ), TRUE );
			DrawFormatString( 10, 40, GetColor( 255, 255, 255 ),
							  game.GetLocalPlayer( ).selectedUnit->name.c_str( ) );
			DrawFormatString( 10, 60, GetColor( 255, 255, 255 ),
							  "TileQ: %d", game.GetLocalPlayer( ).selectedUnit->GetTilePosition( ).q );
			DrawFormatString( 10, 80, GetColor( 255, 255, 255 ),
							  "TileR: %d", game.GetLocalPlayer( ).selectedUnit->GetTilePosition( ).r );
			DrawFormatString( 10, 100, GetColor( 255, 255, 255 ),
							  "PosX: %d", ( int )game.GetLocalPlayer( ).selectedUnit->positionX );
			DrawFormatString( 10, 120, GetColor( 255, 255, 255 ),
							  "PosY: %d", ( int )game.GetLocalPlayer( ).selectedUnit->positionY );
			DrawFormatString( 10, 110, GetColor( 255, 255, 255 ),
							  "TargetX: %d", ( int )game.GetLocalPlayer( ).selectedUnit->targetX );
			DrawFormatString( 10, 130, GetColor( 255, 255, 255 ),
							  "TargetY: %d", ( int )game.GetLocalPlayer( ).selectedUnit->targetY );

		}
	} else {
		showUnitInfo = false;
	}

	Position world_pos = camera.convertScreenToFieldPosition( mouseX, mouseY );

	DrawFormatString( 500, 10, GetColor( 255, 255, 255 ),
					  "PlayerId: %d", game.localPlayerId );
	DrawFormatString( 500, 30, GetColor( 255, 255, 255 ),
					  "MouseX: %d", mouseX );
	DrawFormatString( 500, 50, GetColor( 255, 255, 255 ),
					  "MouseY: %d", mouseY );
	DrawFormatString( 500, 70, GetColor( 255, 255, 255 ),
					  "CameraX: %d", ( int )world_pos.x );
	DrawFormatString( 500, 90, GetColor( 255, 255, 255 ),
					  "CameraY: %d", ( int )world_pos.y );
	DrawFormatString( 500, 150, GetColor( 255, 255, 255 ),
					  "End: %d", game.GetLocalPlayer( ).endTurn );
	DrawFormatString( 500, 170, GetColor( 255, 255, 255 ),
					  "TurnNum: %d", game.currentTurn );

	const Tile* tile = board.GetTileAt( world_pos.x, world_pos.y );
	if ( tile != nullptr ) {
		TilePosition targetTile = ScreenToTile( world_pos.x, world_pos.y );
		double tx, ty;
		TileToScreen( targetTile.q, targetTile.r, tx, ty );

		DrawFormatString( 500, 110, GetColor( 255, 255, 255 ),
						  "MouseTileQ: %d", targetTile.q );
		DrawFormatString( 500, 130, GetColor( 255, 255, 255 ),
						  "MouseTileR: %d", targetTile.r );
		DrawFormatString( 500, 190, GetColor( 255, 255, 255 ),
						  "TileType: %d",tile->GetTileType() );
		//DrawFormatString( 10, 110, GetColor( 255, 255, 255 ),
		//				  "MouseTileX: %d", ( int )tx );
		//DrawFormatString( 10, 130, GetColor( 255, 255, 255 ),
		//				  "MouseTileY: %d", ( int )ty );
		//DrawFormatString( 10, 190, GetColor( 255, 255, 255 ),
		//				  "Action: %d", tile->action );
	}
}

void GameLoopScene::DebugSwitchActivePlayer( ) {
	if ( InputManager::GetKeyDown( KEY_INPUT_TAB ) ) {
		game.SwitchActivePlayer( );
	}
}