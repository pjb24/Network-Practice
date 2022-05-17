//Client Code
//Author: Jacob Preston 2019-04-04

#include "Client.h"
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#define Sleep(duration) usleep(duration*1000)
#endif // !_WIN32


using namespace PNet;

int main()
{
	Client client;
	if ( client.Connect( IPEndpoint( "::1", 6112 ) ) )
	{
		while ( client.IsConnected() )
		{
			client.Frame();
		}
	}
	Network::Shutdown();

	system( "pause" );

	return 0;
}
