solution "undicht workspace"
	language "C++"
	buildoptions "-std=c++11"
    configurations { "debug - windows","debug - linux", "release - windows", "release - linux" }


include "undicht"	
include "sandbox"
