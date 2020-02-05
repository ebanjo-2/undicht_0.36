-- the premake4 file used to build the undicht core project


-- the project for the classes used to load the other core libraries

project "core"
    kind "SharedLib"

	files { "include/**.*", "development_log.txt" }

	includedirs { "include" }
	
	configuration "debug - linux"
		links { "dl" }
		flags { "Symbols" }
		
	configuration "release - linux"
		links { "dl" }
		flags { "OptimizeSpeed", "OptimizeSize" }
		
	configuration "debug - windows"
		flags { "Symbols" }

	configuration "release - windows"
		flags { "OptimizeSpeed", "OptimizeSize" }



-- the core shared libs
include "implementation/graphics/opengl_33"
include "implementation/window/glfw"
include "implementation/audio/openal"
    
