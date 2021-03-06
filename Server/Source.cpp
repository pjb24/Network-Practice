//Server Code
//Author: Jacob Preston 2019-04-04

#include "MyServer.h"
#include <iostream>

int main()
{
	if ( Network::Initialize() )
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		MyServer server;
		if ( server.Initialize( IPEndpoint( "::", 6112 ) ) )
		{
			while ( true )
			{
				server.Frame();
			}
		}
	}
	Network::Shutdown();

	system( "pause" );
	return 0;
}
