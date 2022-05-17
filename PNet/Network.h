#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#endif // _WIN32

namespace PNet
{
	class Network
	{
	public:
		static bool Initialize();
		static void Shutdown();
	};
}
