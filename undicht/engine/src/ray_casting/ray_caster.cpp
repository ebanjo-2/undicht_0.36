#include "ray_caster.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"
#include "graphics/vertex_buffer.h"
#include <core/buffer_layout.h>
#include <core/types.h>

#include <iostream>

namespace undicht {

    // some constants
    const int screen_width = 800;
    const int screen_height = 600;

    // vertices for two triangles covering the whole screen
    const float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,

        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };

    const core::BufferLayout vbo_layout({core::UND_VEC3F});

    const char* screen_shader_src = // for opengl 3.3
        "#vertex\n"
        "#version 330 core\n"

        "layout(location = 0) in vec3 aPos;\n"
        "out vec2 uv;\n"
        "void main(){\n"
        "	uv = aPos.xy * vec2(0.5, -0.5) + vec2(0.5,0.5);\n"
        "	gl_Position = vec4(aPos, 1);\n"
        "} \n"

        "#fragment\n"
        "#version 330 core \n"

        "in vec2 uv;\n"
        "out vec4 FragColor;\n"
        "uniform float time;\n"
        "uniform sampler2D color;\n"
        "void main(){\n"
        "	FragColor = texture(color, uv);\n"
        "}\n\0";

    // the buffer for the output of the renderer
    unsigned char pixel_buffer[screen_width * screen_height * 3];

    // stuff to draw the pixel_buffer to the screen
    graphics::Texture* screen_buffer = 0; // have to be pointers so that they are created once the core is initialized
    graphics::Renderer* renderer = 0;
    graphics::Shader* screen_shader = 0; // the one used to draw the final result onto the screen
    graphics::VertexBuffer* screen_quad = 0;


    RayCaster::RayCaster() {

        if(!screen_buffer)
            screen_buffer = new graphics::Texture;
        if(!renderer)
            renderer = new graphics::Renderer;
        if(!screen_shader)
            screen_shader = new graphics::Shader;
        if(!screen_quad)
            screen_quad = new graphics::VertexBuffer;


        screen_shader->loadSource(std::string(screen_shader_src));

        screen_quad->setData(vertices, 2 * 3 * 3 * sizeof(float));
        screen_quad->setLayout(vbo_layout);

        screen_buffer->setName("color");
        screen_buffer->setSize(screen_width, screen_height);

        renderer->submit(screen_shader);
        renderer->submit(screen_quad);


    }

    RayCaster::~RayCaster() {
        //dtor

        delete screen_buffer;
        delete renderer;
        delete screen_shader;
    }

    void RayCaster::draw(const Wall& wall) {

        const float wall_height = 2;

        // rendering to the pixelbuffer
        glm::vec2 corner_0;
        glm::vec2 corner_1;
        glm::vec2 corner_2;
        glm::vec2 corner_3;


        // calculating the positions of the corners on the screen
        toScreenCoords(wall.m_pos_0, corner_0);
        toScreenCoords(wall.m_pos_0 + wall_height, corner_1);
        toScreenCoords(wall.m_pos_1, corner_2);
        toScreenCoords(wall.m_pos_1 + wall_height, corner_3);

        std::cout << "corner 0 " << corner_0.x << " " << corner_0.y << "\n";
        std::cout << "corner 1 " << corner_1.x << " " << corner_1.y << "\n";
        std::cout << "corner 2 " << corner_2.x << " " << corner_2.y << "\n";
        std::cout << "corner 3 " << corner_3.x << " " << corner_3.y << "\n";

        // drawing lines between the corners
        drawLine(corner_0, corner_1);
        drawLine(corner_1, corner_2);
        drawLine(corner_2, corner_3);
        drawLine(corner_3, corner_1);
        drawLine(corner_0, corner_3);
        drawLine(corner_0, corner_2);

        // displaying the result on the screen
        screen_buffer->setData((char*)pixel_buffer, screen_width * screen_height * 3);
        screen_shader->loadTexture(*screen_buffer);
        renderer->draw();
    }

    void RayCaster::submit(const Camera& cam){

        m_cam = cam;
    }

    void RayCaster::drawLine(glm::vec2 pos_0, glm::vec2 pos_1){

        glm::vec3 color(255,0,0); // the color with which the line gets drawn


        const float total_steps = screen_width + screen_height; // too much, but definitly enough
        glm::vec2 v = (pos_1 - pos_0) / total_steps;


        for(int i = 0; i < total_steps; i++){

            // coloring the pixels on the line
            int x = screen_width * ((pos_0.x + v.x * i) * 0.5 + 0.5);
            int y = screen_height * ((pos_0.y + v.y * i) * -0.5 + 0.5);

            if((x < screen_width) && (x >= 0) && (y < screen_height) && (y >= 0)){
                pixel_buffer[(x + y * screen_width) * 3 + 0] = (unsigned char) color.x;
                pixel_buffer[(x + y * screen_width) * 3 + 1] = (unsigned char) color.y;
                pixel_buffer[(x + y * screen_width) * 3 + 2] = (unsigned char) color.z;
            }
        }

    }

    void RayCaster::toScreenCoords(const glm::vec3& world_pos, glm::vec2& result){
        // the result will be in the range of -1 to 1 for points visible with the fov

        const float near_plane = 0.1; // the plane that represents the screen

        // the trick is to draw a line from the camera to the world_pos, and then see where it intersects with the near_plane
        // np: (x - p) * n = 0
        // with x being a point on the near_plane (np), p being a point on the np 0.1 units infront of the camera
        // and n being the normal to np (view direction of the camera)

        glm::vec3 n = glm::vec3(0,0,-1); // the cam is always looking along the z axis, the world is being rotated around it
        glm::vec3 p = m_cam.m_pos + near_plane * n;

        // ray from the cam to world_pos: ray: x = cam + f * v
        // with x being a point on the ray and cam the position of the camera, v being (world_pos - cam) (normalized)
        // and f being a float bigger then 0

        glm::vec3 cam = m_cam.m_pos;
        glm::vec3 v = glm::normalize(world_pos - cam);

        // the intersection would be (replacing x in the definition of np with the ray definition):
        // (cam + f * v - p) * n = 0
        // solving for f:
        // cam * n + f * v * n - p * n  = 0
        // f = (- cam * n + p * n) / (v * n) which can be shortened to f = (p - cam) * n / (v* n )
        // there is a case where f does not exist: v * n = 0
        // which means that the line is parallel to the plane
        // either it is part of the plane or the two never intersect

        glm::vec3 intersection; // the intersection between the ray and the plane

        if(glm::dot(v, n) == 0){
            // parallel
        } else {
            float f = glm::dot((p - cam), n) / glm::dot(v, n);
            intersection = cam + f * v; // point of intersection of np and the view ray

            // if f is negative, the world_pos is "behind" the camera, which means the point is not on the screen
            // fovs greater then 180 degrees are not possible with the current calculation
        }

        // scaling the intersection based on the fov
        // so that visible points are in the range of -1 to 1

        float fov_width = glm::tan(m_cam.m_FoV) * near_plane; // the max x position on the near plane that is visible for the given fov
        float fov_height = glm::tan(m_cam.m_FoV) * near_plane;

        glm::vec2 scaled_inters = glm::vec2(intersection.x, intersection.y) * glm::vec2(1/fov_width, 1/fov_height);

        result = glm::vec2(scaled_inters.x, world_pos.y);
    }

} // undicht
