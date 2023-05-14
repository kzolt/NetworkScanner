#pragma once

#include <memory>

namespace NS {

	class Scanner
	{
	public:
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		virtual void PrintVendorInfo() = 0;

	public:
		static std::shared_ptr<Scanner> Create();
	};

}