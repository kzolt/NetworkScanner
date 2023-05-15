#pragma once

#include <memory>

namespace NS {

	class Scanner
	{
	public:
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;

		virtual void PrintVendorInfo() const = 0;

	private:
		virtual void GatherDevices() = 0;

	public:
		static std::shared_ptr<Scanner> Create();
	};

}