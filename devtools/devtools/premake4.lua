project "dev_tools"

	kind "ConsoleApp"
	
	language "c++"
	buildoptions "-std=c++11"
	
	includedirs {"src"}
	files {"main.cpp", "src/**.*" } 
