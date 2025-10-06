#include "OnlineScene.h"
#include "DxLib.h"
#include <thread>
#include <chrono>

OnlineScene::OnlineScene( ) :
gameLoopScene(&network){ 

}

void OnlineScene::Run( double deltaTime ) {
	if ( !initialize ) { 
		Initialize( );
	}

	network.PollEvents( );
	gameLoopScene.Run( 1.0 / 60.0,isHost );

	if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 ) { 
		network.Send( "Hello Test Player" );
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
	}

	//std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
}

void OnlineScene::Initialize( ) { 
	int res = MessageBoxA( NULL, "サーバーで起動？", "起動選択", MB_YESNO );
	if ( res == IDYES ) {
		isHost = true;
		network.Host( 1234 );
	} else {
		isHost = false;
		network.Connect( "localhost", 1234 );
	}
	initialize = true;
}