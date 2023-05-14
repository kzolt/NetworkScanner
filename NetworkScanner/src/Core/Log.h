#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace NS {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Core Log Macros
#define NS_TRACE(...)	::NS::Log::GetLogger()->trace(__VA_ARGS__);
#define NS_INFO(...)	::NS::Log::GetLogger()->info(__VA_ARGS__);
#define NS_WARN(...)	::NS::Log::GetLogger()->warn(__VA_ARGS__);
#define NS_ERROR(...)	::NS::Log::GetLogger()->error(__VA_ARGS__);
#define NS_FATAL(...)	::NS::Log::GetLogger()->critical(__VA_ARGS__);
