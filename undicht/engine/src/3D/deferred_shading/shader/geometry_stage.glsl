#vertex
#version 330 core

// inputs from vertex buffer
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

// outputs to fragment shader
out vec2 uv;

// camera uniforms
uniform mat4 view;
uniform mat4 projection;

// model uniforms
uniform mat4 model;
uniform vec3 scale;


void main() {
    
    uv = aUv;

    gl_Position = projection * view * model * vec4(aPos * scale, 1.0);

}




#fragment
#version 330 core

// inputs from vertex shader
in vec2 uv;

// outputs to geometry buffer
out vec3 albedo;


uniform sampler2D color;


void main() {
    
    albedo = texture(color, uv).rgb;

}
