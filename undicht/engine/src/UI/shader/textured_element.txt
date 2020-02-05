#vertex
#version 330 core

layout(location = 0) in vec2 aPos;

out vec2 uv;

uniform vec2 position;
uniform vec2 scale;

void main(){
	
	uv = aPos * vec2(0.5, 0.5) + vec2(0.5,0.5);
	gl_Position = vec4(aPos * scale + position, 0, 1);
} 

#fragment
#version 330 core 

in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform sampler2D color;
uniform vec2 uv_scale = vec2(1,1);


void main(){
	
	vec4 tex_color = texture(color, uv * uv_scale);
   
	if(tex_color.a == 0) discard;
   
	FragColor = tex_color;
}
