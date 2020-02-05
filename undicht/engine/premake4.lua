-- the premake4 file used to build the undicht core project


-- the project for the classes used to load the other core libraries

project "engine"
    kind "SharedLib"

	files {  "src/**.*" }

	includedirs { "../core/include", "src", "../vendor" }
	
	links { "core"  }
	
	configuration "debug - linux"
		links { "dl" }
		flags { "Symbols" }
		
	configuration "release - linux"
		links { "dl" }
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		flags { "Symbols" }

	configuration "release - windows"
		flags { "OptimizeSpeed" }

	
    
