#pragma once

#include <enet/enet.h>

#include <functional>
#include <string>
#include <iostream>


enum class NetworkRole {
	Host,
	Client,
	None
};

class NetworkManager {
public:
	NetworkManager( );
	~NetworkManager( );

	NetworkRole role = NetworkRole::None;
	std::function<void( const std::string& )> onReceiveCallback;

	bool Init( );
	void Shutdown( );

	bool Host( unsigned short port, size_t maxClients = 32);
	bool Connect(const std::string& host, unsigned short port );

	void PollEvents( );

	void Send( const std::string& message );

	bool IsServer( ) const { return isServer; }

private:
	ENetHost* host = nullptr;
	ENetPeer* peer = nullptr;
	bool isServer = false;
};

