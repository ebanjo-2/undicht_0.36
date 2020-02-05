#include "sprite_renderer.h"

#include "graphics/renderer.h"
#include <2D/sprite_shader_src.h>
#include <graphics/uniform.h>
#include <core/types.h>

#include <core/event_logger.h>

#include <glm/glm/gtc/type_ptr.hpp> // for glm::value_ptr

using namespace undicht::graphics;
using namespace undicht::core;


namespace undicht {

    graphics::Shader* SpriteRenderer::s_shader;
    graphics::Shader* SpriteRenderer::s_animation_shader;
    graphics::VertexBuffer* SpriteRenderer::s_quad_vbo;


    int SpriteRenderer::s_renderer_count = 0;

    SpriteRenderer::SpriteRenderer() {
        if(!s_renderer_count) {
            // initializing the static objects

            s_shader = new graphics::Shader;
            s_animation_shader = new graphics::Shader;
            s_quad_vbo = new graphics::VertexBuffer;

            s_shader->loadSource(std::string(sprite_shader_src));
            s_animation_shader->loadSource(std::string(anim_sprite_shader_src));

            s_quad_vbo->setData(quad_vertices, 2 * 6 * sizeof(float));
            s_quad_vbo->setLayout(quad_vbo_layout);

            submit(s_quad_vbo);
        }

        s_renderer_count += 1;
    }

    SpriteRenderer::~SpriteRenderer() {
        //dtor

        s_renderer_count -= 1;

        if(!s_renderer_count) {
            // deleting the static objects

            delete s_shader;
            delete s_quad_vbo;
        }

    }

    void SpriteRenderer::drawSprite(Sprite& sprite) {

        Uniform position;
        Uniform scale;
        Uniform uv_scale;

        position.setName("position");
        position.setData(glm::value_ptr(sprite.getPosition()), UND_VEC3F);

        scale.setName("scale");
        scale.setData(glm::value_ptr(sprite.getScale()), UND_VEC2F);

        uv_scale.setName("uv_scale");
        uv_scale.setData(glm::value_ptr(sprite.m_uv_scale), UND_VEC2F);

        s_shader->loadTexture(sprite);
        s_shader->loadUniform(position);
        s_shader->loadUniform(scale);
        s_shader->loadUniform(uv_scale);


        submit(s_shader);
        draw();
    }

    void SpriteRenderer::drawSprite(AnimatedSprite& sprite) {

        Uniform position;
        Uniform scale;
        Uniform current_texture;
        Uniform uv_scale;


        position.setName("position");
        position.setData(glm::value_ptr(sprite.getPosition()), UND_VEC3F);

        scale.setName("scale");
        scale.setData(glm::value_ptr(sprite.getScale()), UND_VEC2F);

        uv_scale.setName("uv_scale");
        uv_scale.setData(glm::value_ptr(sprite.m_uv_scale), UND_VEC2F);

        int ca = sprite.getCurrentTextureID();
        current_texture.setName("current_texture");
        current_texture.setData(&ca, UND_INT);

        if(sprite.m_current_animation) {
            s_animation_shader->loadTexture(sprite.m_current_animation->m_texture_source);
        } else {
            EventLogger::storeNote(Note(UND_ERROR, "AnimatedSprite cant be rendered cause there is no Animation set", UND_CODE_ORIGIN));
            return;
        }

        s_animation_shader->loadUniform(position);
        s_animation_shader->loadUniform(scale);
        s_animation_shader->loadUniform(current_texture);
        s_animation_shader->loadUniform(uv_scale);

        submit(s_animation_shader);
        draw();
    }


} // undicht
