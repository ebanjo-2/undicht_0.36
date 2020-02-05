project "window_glfw"
    
    kind "SharedLib" 

    files { "src/**.*" }
	
	
    includedirs { "../../../include", "src", "../../../../vendor/glfw/undicht" }
	
	configuration "debug - linux"
		libdirs { "../../../../vendor/glfw/undicht/GLFW/linux" }
		links { "glfw3", "core", "pthread", "dl", "Xxf86vm", "Xrandr", "Xinerama", "Xcursor", "X11" }
		flags { "Symbols" }
		
	configuration "release - linux"
		libdirs { "../../../../vendor/glfw/undicht/GLFW/linux" }
		links { "glfw3", "core", "pthread", "dl", "Xxf86vm", "Xrandr", "Xinerama", "Xcursor", "X11" }
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		libdirs { "../../../../vendor/glfw/undicht/GLFW/windows" }
		links { "glfw3", "gdi32", "opengl32", "core" }
		flags { "Symbols" }
		
	configuration "release - windows"
		libdirs { "../../../../vendor/glfw/undicht/GLFW/windows" }
		links { "glfw3", "gdi32", "opengl32", "core" }
		flags { "OptimizeSpeed"}




