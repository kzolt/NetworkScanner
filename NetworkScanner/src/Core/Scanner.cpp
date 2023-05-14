#include "pch.h"
#include "Scanner.h"

#include "Platforms/Windows/WindowsScanner.h"

namespace NS {

	std::shared_ptr<Scanner> Scanner::Create()
	{
		switch (Application::GetApplication()->GetCurrentPlatform())
		{
			case Platform::Windows:		return std::make_shared<WindowsScanner>();
			case Platform::MacOS:		return nullptr;
			case Platform::Linux:		return nullptr;
		}

		return nullptr;
	}

}