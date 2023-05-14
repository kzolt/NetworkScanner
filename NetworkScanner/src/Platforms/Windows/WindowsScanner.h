#pragma once

#include "Core/Scanner.h"

namespace NS {

	class WindowsScanner : public Scanner
	{
	public:
		WindowsScanner() = default;
		~WindowsScanner() = default;

		virtual bool Init() override;
		virtual void Shutdown() override;

		virtual void PrintVendorInfo() override;

	private:

	};

}