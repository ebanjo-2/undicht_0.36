#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "2D/sprite.h"
#include "2D/animated_sprite.h"
#include <graphics/renderer.h>
#include <graphics/shader.h>
#include <graphics/vertex_buffer.h>

namespace undicht {


    class SpriteRenderer : public graphics::Renderer {

        private:
            static graphics::Shader* s_shader;
            static graphics::Shader* s_animation_shader;
            static graphics::VertexBuffer* s_quad_vbo;

            static int s_renderer_count; // to keep track of the number of sprite renderers so that the static pointers can be deleted when the last one gets destructed

        public:


            void drawSprite(Sprite& sprite);
            void drawSprite(AnimatedSprite& sprite);

            SpriteRenderer();
            virtual ~SpriteRenderer();


    };

} // undicht

#endif // SPRITERENDERER_H
