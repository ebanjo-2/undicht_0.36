#include "sprite_shader_src.h"

namespace undicht {
    // the shader for rendering 2D sprites

    const char* sprite_shader_src =
        "#vertex\n"
        "#version 330 core\n"

        "layout(location = 0) in vec2 aPos;\n"
        "out vec2 uv;\n"
        "uniform vec3 position;\n"
        "uniform vec2 scale;"
        "void main(){\n"
        "	uv = aPos * vec2(0.5, 0.5) + vec2(0.5,0.5);\n"
        "	gl_Position = vec4(aPos.xy * scale + position.xy, position.z, 1);\n"
        "} \n"

        "#fragment\n"
        "#version 330 core \n"

        "in vec2 uv;\n"
        "out vec4 FragColor;\n"
        "uniform float time;\n"
        "uniform sampler2D color;\n"
        "uniform vec2 uv_scale;"
        "void main(){\n"
        "   vec4 tex_color = texture(color, uv * uv_scale);\n"
        "   if(tex_color.a == 0) discard;\n"
        "	FragColor = tex_color;\n"
        "}\n\0";

    const char* anim_sprite_shader_src =
        "#vertex\n"
        "#version 330 core\n"

        "layout(location = 0) in vec2 aPos;\n"
        "out vec2 uv;\n"
        "uniform vec3 position;\n"
        "uniform vec2 scale;"
        "void main(){\n"
        "	uv = aPos * vec2(0.5, 0.5) + vec2(0.5,0.5);\n"
        "	gl_Position = vec4(aPos.xy * scale + position.xy, position.z, 1);\n"
        "} \n"

        "#fragment\n"
        "#version 330 core \n"

        "in vec2 uv;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2DArray texture_source;\n"
        "uniform int current_texture; "
        "uniform vec2 uv_scale;"

        "void main(){\n"
        "   vec4 tex_color = texture(texture_source, vec3(uv * uv_scale, current_texture));\n"
        "   if(tex_color.a <= 0.4) discard;\n"
        "	FragColor = tex_color;\n"
        "}\n\0";

    // the quad for all sprites
    const float quad_vertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,

        1.0f,  1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f
    };

    const core::BufferLayout quad_vbo_layout = core::BufferLayout({core::UND_VEC2F});


} // undicht
