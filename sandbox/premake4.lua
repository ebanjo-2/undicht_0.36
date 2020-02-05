

    project "sandbox"

        kind "ConsoleApp"
        files { "src/**.*" }
		includedirs { "src", "../undicht/core/include","../undicht/engine/src", "../undicht/vendor", "../undicht/vendor/glm" }
		links { "core", "engine" }
		
		configuration "debug - linux"
			links { "dl" }
			
		configuration "release - linux"
			links { "dl" }
			

        
