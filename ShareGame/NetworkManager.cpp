#include "NetworkManager.h"
#include "DxLib.h"
NetworkManager::NetworkManager( ) { 
	if ( enet_initialize( ) != 0 ) { 
		std::cerr << "Failed to inintialize ENet.\n";
		MessageBoxA( NULL, "ENet èâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ", "Error", MB_OK );
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
		while ( enet_host_service(host,&event,10) > 0 ) {
			switch ( event.type ) {
			case ENET_EVENT_TYPE_CONNECT: {
					peer = event.peer;
					MessageBoxA( NULL, "ê⁄ë±ÇµÇ‹ÇµÇΩ", "Connect", MB_OK );
					break; 
			}
			case ENET_EVENT_TYPE_RECEIVE:{
					std::string msg( reinterpret_cast< char* >( event.packet->data ), event.packet->dataLength );
					DrawFormatString( 10, 10, GetColor( 255, 0, 0 ), "Message: %s", msg.c_str() );

					if ( onReceiveCallback ) { 
						onReceiveCallback( msg );
					}

					enet_packet_destroy( event.packet );
					break;
				}
			case ENET_EVENT_TYPE_DISCONNECT:
				{
					MessageBoxA( NULL, "ê⁄ë±èIóπÇµÇ‹ÇµÇΩ", "Disconnect", MB_OK );
					DrawFormatString( 10, 10, GetColor( 255, 255, 255 ), "Client disconnected." );
					std::cout << "Client disconnected." << std::endl;
					break;
				}
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
		enet_host_flush( host );
	} else if ( peer ) { 
		ENetPacket* packet = enet_packet_create( message.c_str( ),
												 message.size( ) + 1, ENET_PACKET_FLAG_RELIABLE );
		enet_peer_send( peer, 0, packet );
		enet_host_flush( host );
	}
}
