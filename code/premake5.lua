workspace "TobiiWorkspace"
	configurations { "Debug", "Release" }

	filter "configurations:*"
		architecture "x86_64"

	systemversion("10.0.17134.0")

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
		targetsuffix ("-release")

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols("On")
		targetsuffix ("-debug")

project "Tobii_code"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin"
	targetname ("tobii_exec")
	targetextension (".exe")

	vpaths { 
		["Headers/*"] = {"src/**.h", "src/**.hpp"},
		["Sources/*"] = {"src/*.c", "src/*.cpp"}
	}

	files { "src/**.h", "src/**.cpp" }
	
	includedirs { "include" }

	libdirs { "lib" }

	links {
		"tobii_stream_engine", 
		"SDL2main",
		"SDL2",
		"SDL2_image",
		"SDL2_mixer",
		"SDL2_ttf" 
	}

	-- postbuildcommands {
	-- 	-- Copy the SDL2 dll to the Bin folder.
	-- 	'{COPY} "lib/*.dll" "%{cfg.targetdir}"'
	-- }
