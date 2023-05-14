#pragma once

#include "Core/Scanner.h"

namespace NS {

	class WindowsScanner : public Scanner
	{
	public:
		WindowsScanner() = default;
		~WindowsScanner() = default;

		virtual void Init() override;
		virtual void Shutdown() override;

	private:

	};

}