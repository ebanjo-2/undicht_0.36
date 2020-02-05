this is a game engine I work on in my spare time
It is the current version of a project i worked on since about 3 years, 
when i started to try to make my own game engine in java with the things i had learnd from
ThinMatrix's lwjgl/opengl tutorial series on youtube
I switched to c++ in september of 2017 when i found the website learnopengl.com,
witch really helped me to understand and use opengl

Getting started:
clone repos, run premake4 codeblocks (or whatever ide you want),
open the workspace, build the core project first, then the other ones
you should have build all of them before trying to run the sandbox example application
If youre on linux, you will probably have trouble getting the glfw window implementation library to link
If thats the case, you may have to build glfw on your system and place the resulting static lib in 
undicht/vendor/glfw/undicht/linux
