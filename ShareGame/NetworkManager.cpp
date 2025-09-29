#include "NetworkManager.h"
#include "DxLib.h"
NetworkManager::NetworkManager( ) { 
	if ( enet_initialize( ) != 0 ) { 
		std::cerr << "Failed to inintialize ENet.\n";
		MessageBoxA( NULL, "ENet ‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "Error", MB_OK );
	}
}

NetworkManager::~NetworkManager( ) { 
	Shutdown( );
	enet_deinitialize( );
}

bool NetworkManager::Init( ) { 
	//role = selectedRole;
	//if ( enet_initialize( ) != 0 ) {
	//	return false;
	//}

	//if ( role == NetworkRole::Host ) { 
	//	ENetAddress address;
	//	address.host = ENET_HOST_ANY;
	//	address.port = 12345;

	//	host = enet_host_create( &address, 32, 2, 0, 0 );

	//	if ( !host ) { 
	//		return false;
	//	}
	//} else if ( role == NetworkRole::Client ) { 
	//	host = enet_host_create( nullptr, 1, 2, 0, 0 );
	//	if ( !host ) { 
	//		return false;
	//	}
	//}

	return true;
}

void NetworkManager::Shutdown( ) { 
	if ( peer ) { 
		enet_peer_disconnect( peer, 0 );
		peer = nullptr;
	} 

	if ( host ) { 
		enet_host_destroy( host );
		host = nullptr;
	}
	//enet_deinitialize( );
}

bool NetworkManager::Host( unsigned short port, size_t maxClients  ) {
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;

	host = enet_host_create( &address, maxClients, 2, 0, 0 );
	if ( !host ) { 
		return false;
	}

	isServer = true;
	return true;
}

bool NetworkManager::Connect( const std::string& hostname, unsigned short port ) { 
	host = enet_host_create( nullptr, 1, 2, 0, 0 );

	if ( !host ) { 
		return false;
	}

	ENetAddress address;
	enet_address_set_host( &address, hostname.c_str( ) );
	address.port = port;

	peer = enet_host_connect( host, &address, 2, 0 );
	if ( !peer ) {
		return false;
	}

	return true;
}

void NetworkManager::PollEvents( ) {
	if ( !host ) return;

	ENetEvent event;
		while ( enet_host_service(host,&event,0) > 0 ) {
			switch ( event.type ) {
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "A new client connected!" << std::endl;
				DrawFormatString( 10, 10, GetColor( 255, 255, 255 ),"A new client connected!");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				DrawFormatString( 10, 10, GetColor( 255, 255, 255 ), "Message: %s" , ( char* )event.packet->data );
				enet_packet_destroy( event.packet );
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				DrawFormatString( 10, 10, GetColor( 255, 255, 255 ), "Client disconnected." );
				std::cout << "Client disconnected." << std::endl;
				break;
	
			default:
				DrawFormatString( 10, 10, GetColor( 255, 255, 255 ), "default" );
				break;
			}
		}
}

void NetworkManager::Send( const std::string& message ) { 
	if ( isServer ) { 
		ENetPacket* packet = enet_packet_create( message.c_str( ),
												 message.size( ) + 1, ENET_PACKET_FLAG_RELIABLE );
		enet_host_broadcast( host, 0, packet );
	} else if ( peer ) { 
		ENetPacket* packet = enet_packet_create( message.c_str( ),
												 message.size( ) + 1, ENET_PACKET_FLAG_RELIABLE );
		enet_peer_send( peer, 0, packet );
	}
}

//void NetworkManager::Update( ) { 
//	ENetEvent event;
//	while ( enet_host_service(host,&event,0) > 0 ) {
//		switch ( event.type ) {
//		case ENET_EVENT_TYPE_CONNECT:
//			peer = event.peer;
//			break;
//
//		case ENET_EVENT_TYPE_DISCONNECT:
//			peer = nullptr;
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	if ( role == NetworkRole::Host ) { 
//	
//	}else if ( role == NetworkRole::Client && peer ) { 
//
//	}
//}