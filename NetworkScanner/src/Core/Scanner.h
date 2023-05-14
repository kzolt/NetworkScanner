#pragma once

#include <memory>

namespace NS {

	class Scanner
	{
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		static std::shared_ptr<Scanner> Create();
	};

}