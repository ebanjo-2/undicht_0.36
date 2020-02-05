project "audio_openal"
    
    kind "SharedLib" 

    files { "src/**.*" }
    
    links { "core" }

    includedirs { "../../../include", "../../../../vendor/openal/undicht/", "src" }
	
	configuration "debug - linux"
		libdirs { "../../../../vendor/openal/undicht/linux" }
		links { "openal" }
		flags { "Symbols" }
		
	configuration "release - linux"
		libdirs { "../../../../vendor/openal/undicht/linux" }
		links { "openal" }
		flags { "OptimizeSpeed"}
		
		
	configuration "debug - windows"
		libdirs { "../../../../vendor/openal/undicht/windows" }
		links { "OpenAL32" }
		flags { "Symbols" }

	configuration "release - windows"
		libdirs { "../../../../vendor/openal/undicht/windows" }
		links { "OpenAL32" }
		flags { "OptimizeSpeed"}
	
