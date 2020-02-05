project "video_opengl_33"
    
    kind "SharedLib" 

    files { "src/**.*", "../../../../vendor/glad/undicht/**.*" }
    
    links { "core" }

    includedirs { "../../../include", "src", "../../../../vendor/glad/undicht" }
	
	configuration "debug - linux"
		flags { "Symbols" }
		
	configuration "release - linux"
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		flags { "Symbols" }

	configuration "release - windows"
		flags { "OptimizeSpeed"}