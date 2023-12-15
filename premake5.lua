workspace "WorkCalculator"
	platforms "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputs  = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directories relative to root folder (solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "WorkCalculator/vendor/GLFW/include"
	IncludeDir["glad"] = "WorkCalculator/vendor/glad/include"
	IncludeDir["ImGui"] = "WorkCalculator/vendor/ImGui"

	include "WorkCalculator/vendor/GLFW"
	include "WorkCalculator/vendor/glad"
	include "WorkCalculator/vendor/ImGui"

project "WorkCalculator"
	location "WorkCalculator"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputs  .. "/%{prj.name}")
	objdir ("bin-int/" .. outputs  .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "WorkCalculator/src/pch.cpp"

	files
    {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links 
	{ 
		"GLFW",
		"glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GL_PLATFORM_WINDOWS",
			"GL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "GL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "GL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "GL_DIST"
		buildoptions "/MD"
		optimize "On"
