//Client Code
//Author: Jacob Preston 2019-04-04

#include "MyClient.h"
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#define Sleep(duration) usleep(duration*1000)
#endif // !_WIN32

int main()
{
	if ( Network::Initialize() )
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		MyClient client;
		if ( client.Connect( IPEndpoint( "::1", 6112 ) ) )
		{
			while ( client.IsConnected() )
			{
				client.Frame();
			}
		}
	}
	Network::Shutdown();

	system( "pause" );

	return 0;
}
