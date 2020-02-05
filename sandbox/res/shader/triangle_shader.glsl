#vertex 
#version 330 core

layout(location = 0) in vec3 aPos;

out vec2 uv;

void main(){
	
	uv = aPos.xy + vec2(0.5,0.5);
	
	gl_Position = vec4(aPos, 1);
} 

 
#fragment
#version 330 core 

in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform sampler2D color;

void main(){
	
	FragColor = texture(color, uv);
}