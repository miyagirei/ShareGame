#include "OnlineScene.h"
#include "DxLib.h"
#include <thread>
#include <chrono>

OnlineScene onlineScene;

OnlineScene::OnlineScene( ) :
gameLoopScene(&network){ 

}

void OnlineScene::Run( double deltaTime ) {
	if ( !initialize ) { 
		Initialize( );
	}

	DrawString(10, 10, isHost ? "MODE:HOST" : "MODE:CLIENT", GetColor(255, 255, 0));

	network.PollEvents( );
	gameLoopScene.Run( 1.0 / 60.0,isHost );

	if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 ) { 
		network.Send( "Hello Test Player" );
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
	}

	//std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
}

void OnlineScene::Initialize( ) { 
	if ( isHost ) {
		network.Host( 1234 );
	} else {
		network.Connect( "localhost", 1234 );
	}
	initialize = true;
}