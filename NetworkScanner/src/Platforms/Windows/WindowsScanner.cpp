#include "pch.h"
#include "WindowsScanner.h"

#include <WinSock2.h>
#include <WS2tcpip.h>

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
		s_Data.Service.sin_port = 0;
		s_Data.Service.sin_addr.S_un.S_addr = inet_addr(s_Data.IP);

		if (bind(s_Data.Socket, (SOCKADDR*)&s_Data.Service, sizeof(s_Data.Service)) == SOCKET_ERROR)
		{
			NS_ERROR("Failed to Bind Socket! (Error Code {0}", WSAGetLastError());
			return false;
		}

		return true;
	}

	void WindowsScanner::Shutdown()
	{
		int error = closesocket(s_Data.Socket);
		if (error != 0)
			NS_ERROR("Failed to close socket: Error Code ({0})", WSAGetLastError());

		WSACleanup();
	}

	void WindowsScanner::GatherDevices()
	{
		char* ip_addr;
		char* reverse_hostname;
		struct sockaddr_in addr_con;

		char networks[NI_MAXHOST];
		for (int i = 1; i < 255; ++i)
		{
			char ip[80];
			sprintf(ip, "192.168.1.%d", i);
			ip_addr = DNSLookup(ip, &addr_con);
			if (ip_addr == NULL)
				continue;

			reverse_hostname = ReverseDNSLookup(ip_addr);

			if (reverse_hostname == NULL)
				continue;

			NS_TRACE("Reverse Lookup Domain: {0}\nIp Address: {1}", reverse_hostname, ip);
		}
	}

	void WindowsScanner::PrintVendorInfo() const
	{
		NS_TRACE("=====================================================");
		NS_TRACE("Local Machine Data")
		NS_TRACE("=====================================================");
		NS_TRACE("\tWinSock: {0}", s_Data.Wsa.szDescription);
		NS_TRACE("\tHost Name: {0}", s_Data.Host->h_name);
		NS_TRACE("\tIPv4: {0}", s_Data.IP);
		NS_TRACE("=====================================================");
	}

	char* WindowsScanner::DNSLookup(char* addr_host, struct sockaddr_in* addr_con)
	{
		hostent* host_entity;
		char* ip = (char*)malloc(NI_MAXHOST * sizeof(char));
		int i;

		if ((host_entity = gethostbyname(addr_host)) == NULL)
			return NULL;

		// fill up address structure
		strcpy(ip, inet_ntoa(*(struct in_addr*)host_entity->h_addr_list));

		addr_con->sin_family = host_entity->h_addrtype;
		addr_con->sin_port = 0;
		addr_con->sin_addr.s_addr = inet_addr(ip);

		return ip;
	}

	char* WindowsScanner::ReverseDNSLookup(char* ip_addr)
	{
		struct sockaddr_in temp_addr;
		int len;
		char buffer[NI_MAXHOST];
		char* return_buffer;

		temp_addr.sin_family = AF_INET;
		temp_addr.sin_addr.s_addr = inet_addr(ip_addr);
		len = sizeof(struct sockaddr_in);

		if (getnameinfo((struct sockaddr*)&temp_addr, len, buffer, sizeof(buffer), NULL, 0, NI_NAMEREQD))
			return NULL;

		return_buffer = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(return_buffer, buffer);

		return return_buffer;
	}

}