//Server Code
//Author: Jacob Preston 2019-04-04

#include "Server.h"
#include <iostream>

using namespace PNet;

int main()
{
	Server server;
	if ( server.Initialize( IPEndpoint( "::", 6112 ) ) )
	{
		while ( true )
		{
			server.Frame();
		}
	}
	Network::Shutdown();

	system( "pause" );
	return 0;
}
