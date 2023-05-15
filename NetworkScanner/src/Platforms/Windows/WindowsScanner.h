#pragma once

#include "Core/Scanner.h"

struct sockaddr_in;

namespace NS {

	class WindowsScanner : public Scanner
	{
	public:
		WindowsScanner() = default;
		~WindowsScanner() = default;

        virtual bool Init() override {}
        virtual void Shutdown() override {}

        virtual void PrintVendorInfo() const override {}

	private:
        virtual void GatherDevices() override {}

	private:
        char* DNSLookup(char* addr_host, struct sockaddr_in* addr_con);
        char* ReverseDNSLookup(char* ip_addr);
	};

}
