//Server Code
//Author: Jacob Preston 2019-04-04

#include <PNet/IncludeMe.h>
#include <iostream>

using namespace PNet;

int main()
{
	if ( Network::Initialize() )
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		IPEndpoint test( "www.google.com", 8080 );
		if ( test.GetIPVersion() == IPVersion::IPv4 )
		{
			std::cout << "Hostname: " << test.GetHostname() << std::endl;
			std::cout << "IP: " << test.GetIPString() << std::endl;
			std::cout << "Port: " << test.GetPort() << std::endl;
			std::cout << "IP Bytes... " << std::endl;
			for ( auto& digit : test.GetIPBytes() )
			{
				std::cout << (int)digit << std::endl;
			}
		}
		else
		{
			std::cerr << "This is not an ipv4 address." << std::endl;
		}

		Socket socket;
		if ( socket.Create() == PResult::P_Success )
		{
			std::cout << "Socket successfully created." << std::endl;
			socket.Close();
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();

	system( "pause" );
	return 0;
}
