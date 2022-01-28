workspace "2D-ParticleSim"
	architecture "x64"
	configurations {"Debug", "Release"}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "2D-ParticleSim"
	location "2D-ParticleSim"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/Libraries/include",
	}

	libdirs
	{
		"%{prj.name}/Libraries/lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
	filter "configurations:Debug"
		buildoptions "/MDd"

	filter "configurations:Release"
		buildoptions "/MDd"
		
	links
	{
		"glfw3.lib",
		"opengl32.lib"
	}
