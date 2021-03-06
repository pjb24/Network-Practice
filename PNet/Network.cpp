#include "Network.h"
#include <iostream>

bool PNet::Network::Initialize()
{
#ifdef _WIN32
	WSADATA wsaData;
	int result = WSAStartup( MAKEWORD( 2, 2 ), &wsaData );
	if ( result != 0 )
	{
		std::cerr << "Failed to start up the winsock API." << std::endl;
		return false;
	}

	if ( ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) )
	{
		std::cerr << "Could not find a usable version of the winsock api dll." << std::endl;
		return false;
	}
#endif // _WIN32

	return true;
}

void PNet::Network::Shutdown()
{
#ifdef _WIN32
	WSACleanup();
#endif // _WIN32
}
