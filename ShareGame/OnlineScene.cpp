#include "OnlineScene.h"
#include "DxLib.h"
#include <thread>
#include <chrono>

OnlineScene::OnlineScene( ) { 

}

void OnlineScene::Run( double deltaTime ) {
	if ( !initialize ) { 
		Initialize( );
	}

	network.PollEvents( );

	if ( GetAsyncKeyState( VK_SPACE ) & 0x8000 ) { 
		network.Send( "Hello Test Player" );
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
	}

	std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );
}

void OnlineScene::Initialize( ) { 
	int choice = MessageBoxA( NULL, "サーバーで起動？", "起動選択", MB_YESNO );
	if ( choice == IDYES ) {
		network.Host( 1234 );
	} else {
		network.Connect( "localhost", 1234 );
	}
	initialize = true;
}