#vertex
#version 330 core

layout(location = 0) in vec2 aPos;

out vec2 uv;

uniform vec2 position;
uniform vec2 scale;
uniform float font_size;

layout (std140) uniform text_data {
    vec4 data[2048]; // max of 1024 chars for now
};

void main(){

    vec2 uv_upper_left  = data[gl_InstanceID * 2 + 0].xy;
    vec2 uv_size        = data[gl_InstanceID * 2 + 0].zw;
    vec2 cursor_offset  = data[gl_InstanceID * 2 + 1].xy;
    vec2 char_size      = data[gl_InstanceID * 2 + 1].zw;

    // calculating the uv
    vec2 uv_lower_right = uv_upper_left + uv_size;
	uv = aPos + vec2(0.5,0.5);
    uv = (vec2(1) - uv) * uv_upper_left + uv * uv_lower_right;
    //uv.y = 1 - uv.y;

	gl_Position = vec4(((aPos * uv_size + cursor_offset) * font_size) * scale + position , 0, 1);
} 

#fragment
#version 330 core 

in vec2 uv;

out vec4 FragColor;

uniform vec4 color;
uniform vec4 edge_color;

uniform sampler2D font_map;


void main(){
	
	vec4 tex_color = texture(font_map, uv);

    if(tex_color.a > color.a) {

	    FragColor = color;

    } else if (tex_color.a > edge_color.a) {

        FragColor = edge_color;

    } else {
        
        discard;
    }
   

}
