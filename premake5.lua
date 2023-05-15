workspace "NetworkScanner"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "NetworkScanner"
	location "NetworkScanner"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"NetworkScanner/vendor/spdlog/include",
		"NetworkScanner/src"
	}

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/*.cpp",
		"%{prj.name}/src/Core/*.cpp"

	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		pchheader "pch.h"
		pchsource "NetworkScanner/src/pch.cpp"

		defines
		{
			"NS_PLATFORM_WINDOWS"
		}

		links
		{
			"Ws2_32.lib"
		}

		files
		{
			"%{prj.name}/src/Platforms/Windows/*.cpp"
		}

	filter "system:macosx"
		cppdialect "C++20"
		systemversion "latest"

		pchheader "src/pch.h"

		defines
		{
			"NS_PLATFORM_MACOS"
		}

		externalincludedirs
		{
			"NetworkScanner/vendor/spdlog/include"
		}

		xcodebuildsettings = {  ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

	filter "configurations:Debug"
		defines "NS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NS_RELEASE"
		optimize "On"


	filter "configurations:Dist"
		defines "NS_DIST"
		optimize "On"