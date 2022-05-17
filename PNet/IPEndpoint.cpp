#include "IPEndpoint.h"
#include <assert.h>
#include <iostream>
#include "Helper.h"
#ifndef _WIN32
#include <string.h>
#endif // !_WIN32

namespace PNet
{
	IPEndpoint::IPEndpoint( const char* ip, unsigned short port )
	{
		this->port = port;

		//IPv4
		in_addr addr;	//location to store the ipv4 address
		int result = inet_pton( AF_INET, ip, &addr );

		if ( result == 1 )
		{
			if ( addr.s_addr != INADDR_NONE )
			{
				ip_string = ip;
				hostname = ip;
				Helpers::trim( ip_string );
				Helpers::trim( hostname );

				ip_bytes.resize( sizeof( uint32_t ) );
				memcpy( &ip_bytes[0], &addr.s_addr, sizeof( uint32_t ) );

				ipversion = IPVersion::IPv4;
				return;
			}
		}

		//Attempt to resolve hostname to ipv4 address
		addrinfo hints = {};	//hints will filter the results we get back for getaddrinfo
		hints.ai_family = AF_INET;	//ipv4 addresses only
		addrinfo* hostinfo = nullptr;
		result = getaddrinfo( ip, NULL, &hints, &hostinfo );
		if ( result == 0 )
		{
			sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>( hostinfo->ai_addr );

			//host_addr->sin_addr.s_addr
			ip_string.resize( 16 );
			inet_ntop( AF_INET, &host_addr->sin_addr, &ip_string[0], 16 );

			hostname = ip;
			Helpers::trim( ip_string );
			Helpers::trim( hostname );

			uint32_t ip_long = host_addr->sin_addr.s_addr;
			ip_bytes.resize( sizeof( uint32_t ) );
			memcpy( &ip_bytes[0], &ip_long, sizeof( uint32_t ) );

			ipversion = IPVersion::IPv4;

			freeaddrinfo( hostinfo );
			return;
		}

		//IPv6
		in6_addr addr6;	//location to store the ipv6 address
		result = inet_pton( AF_INET6, ip, &addr6 );

		if ( result == 1 )
		{
			ip_string = ip;
			hostname = ip;
			Helpers::trim( ip_string );
			Helpers::trim( hostname );

			ip_bytes.resize( 16 );
			memcpy( &ip_bytes[0], &addr6, 16 );

			ipversion = IPVersion::IPv6;
			return;
		}

		//Attempt to resolve hostname to ipv6 address
		addrinfo hintsv6 = {};	//hints will filter the results we get back for getaddrinfo
		hintsv6.ai_family = AF_INET6;	//ipv6 addresses only
		addrinfo* hostinfov6 = nullptr;
		result = getaddrinfo( ip, NULL, &hintsv6, &hostinfov6 );
		if ( result == 0 )
		{
			sockaddr_in6* host_addr = reinterpret_cast<sockaddr_in6*>( hostinfov6->ai_addr );

			ip_string.resize( 46 );
			inet_ntop( AF_INET6, &host_addr->sin6_addr, &ip_string[0], 46 );

			hostname = ip;
			Helpers::trim( ip_string );
			Helpers::trim( hostname );

			ip_bytes.resize( 16 );
			memcpy( &ip_bytes[0], &host_addr->sin6_addr, 16 );

			ipversion = IPVersion::IPv6;

			freeaddrinfo( hostinfo );
			return;
		}
	}

	IPEndpoint::IPEndpoint( sockaddr* addr )
	{
		assert( addr->sa_family == AF_INET || addr->sa_family == AF_INET6 );
		if ( addr->sa_family == AF_INET )	//IPv4
		{
			sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>( addr );
			ipversion = IPVersion::IPv4;
			port = ntohs( addrv4->sin_port );
			ip_bytes.resize( sizeof( uint32_t ) );
			memcpy( &ip_bytes[0], &addrv4->sin_addr, sizeof( uint32_t ) );
			ip_string.resize( 16 );
			inet_ntop( AF_INET, &addrv4->sin_addr, &ip_string[0], 16 );
			hostname = ip_string;
		}
		else	//IPv6
		{
			sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>( addr );
			ipversion = IPVersion::IPv6;
			port = ntohs( addrv6->sin6_port );
			ip_bytes.resize( 16 );
			memcpy( &ip_bytes[0], &addrv6->sin6_addr, 16 );
			ip_string.resize( 46 );
			inet_ntop( AF_INET6, &addrv6->sin6_addr, &ip_string[0], 46 );
			hostname = ip_string;
		}
		Helpers::trim( ip_string );
		Helpers::trim( hostname );
	}

	IPVersion IPEndpoint::GetIPVersion()
	{
		return ipversion;
	}

	std::vector<uint8_t> IPEndpoint::GetIPBytes()
	{
		return ip_bytes;
	}

	std::string IPEndpoint::GetHostname()
	{
		return hostname;
	}

	std::string IPEndpoint::GetIPString()
	{
		return ip_string;
	}

	unsigned short IPEndpoint::GetPort()
	{
		return port;
	}

	sockaddr_in IPEndpoint::GetSockaddrIPv4()
	{
		assert( ipversion == IPVersion::IPv4 );
		sockaddr_in addr = {};
		addr.sin_family = AF_INET;
		memcpy( &addr.sin_addr, &ip_bytes[0], sizeof( uint32_t ) );
		addr.sin_port = htons( port );
		return addr;
	}

	sockaddr_in6 IPEndpoint::GetSockaddrIPv6()
	{
		assert( ipversion == IPVersion::IPv6 );
		sockaddr_in6 addr = {};
		addr.sin6_family = AF_INET6;
		memcpy( &addr.sin6_addr, &ip_bytes[0], 16 );
		addr.sin6_port = htons( port );
		return addr;
	}

	void IPEndpoint::Print()
	{
		switch ( ipversion )
		{
			case PNet::IPv4:
				std::cout << "IP Version: IPv4" << hostname << std::endl;
				break;
			case PNet::IPv6:
				std::cout << "IP Version: IPv6" << hostname << std::endl;
				break;
			default:
				std::cout << "IP Version: Unknown" << hostname << std::endl;
				break;
		}
		std::cout << "Hostname: " << hostname << std::endl;
		std::cout << "IP: " << ip_string << std::endl;
		std::cout << "Port: " << port << std::endl;
		std::cout << "IP bytes..." << std::endl;
		for ( auto& digit : ip_bytes )
		{
			std::cout << (int)digit << std::endl;
		}
	}
}
