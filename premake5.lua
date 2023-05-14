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

	targetdir("bin/" .. outputdir .. "%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "%{prj.name}")

	pchheader "pch.h"
	pchsource "NetworkScanner/src/pch.cpp"

	includedirs
	{
		"NetworkScanner/vendor/spdlog/include",
		"NetworkScanner/src"
	}

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"

		defines
		{
			"NS_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NS_RELEASE"
		optimize "On"


	filter "configurations:Dist"
		defines "NS_DIST"
		optimize "On"