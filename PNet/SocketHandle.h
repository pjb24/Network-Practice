#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#endif // _WIN32

namespace PNet
{
#ifdef _WIN32
	typedef SOCKET SocketHandle;
#else
	typedef int SocketHandle;
#endif // _WIN32
}
