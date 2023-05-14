#include "pch.h"
#include "WindowsScanner.h"

#include <WinSock2.h>
#include <iostream>

namespace NS {

	struct Data
	{
		WSADATA Wsa;
		SOCKET Socket;
		sockaddr_in Service;
		hostent* Host;

		char* IP;
		uint16_t port = 27015;
	};

	static Data s_Data;

	bool WindowsScanner::Init()
	{
		// Initialize WinSock
		if (WSAStartup(MAKEWORD(2, 2), &s_Data.Wsa) != 0)
		{
			NS_ERROR("WSAStartup failed! (Error Code {0})", WSAGetLastError());
			return false;
		}

		// Create Socket
		s_Data.Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s_Data.Socket < 0)
		{
			NS_ERROR("Failed to Create Socket! (Error Code {0})", WSAGetLastError());
			return false;
		}

		// Bind socket to local IP Address
		s_Data.Host = gethostbyname("");
		s_Data.IP = inet_ntoa(*(struct in_addr*)*s_Data.Host->h_addr_list);

		s_Data.Service.sin_family = AF_INET;
		s_Data.Service.sin_addr.S_un.S_addr = inet_addr(s_Data.IP);

		if (bind(s_Data.Socket, (SOCKADDR*)&s_Data.Service, sizeof(s_Data.Service)) == SOCKET_ERROR)
		{
			NS_ERROR("Failed to Bind Socket! (Error Code {0}", WSAGetLastError());
			return false;
		}

		// Set Socket Options
		/*int value;
		if (setsockopt(s_SocketHandle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value)))
		{
			NS_ERROR("Failed to set socket options! (Error Code {0})", WSAGetLastError());
			return false;
		}*/

		return true;
	}

	void WindowsScanner::Shutdown()
	{
		int error = closesocket(s_Data.Socket);
		if (error != 0)
			NS_ERROR("Failed to close socket: Error Code ({0})", WSAGetLastError());

		WSACleanup();
	}

	void WindowsScanner::PrintVendorInfo()
	{
		NS_TRACE("=====================================================");
		NS_TRACE("Local Machine Data")
		NS_TRACE("=====================================================");
		NS_TRACE("\tWinSock:\t {0}", s_Data.Wsa.szDescription);
		NS_TRACE("\tHost Name: {0}", s_Data.Host->h_name);
		NS_TRACE("\tIPv4: {0}", s_Data.IP);
		NS_TRACE("=====================================================");
	}

}