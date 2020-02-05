#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <graphics/renderer.h>
#include "2D/sprite_renderer.h"

#include <graphics/shader.h>
#include <graphics/uniform.h>
#include "ui_element.h"


namespace undicht {


    class UIRenderer : public graphics::Renderer {

        private:

            graphics::Uniform m_position_uniform;
            graphics::Uniform m_scale_uniform;

        public:

            static graphics::Shader* s_textured_element_shader;
            static graphics::Shader*s_text_shader;
            static graphics::VertexBuffer* s_quad_vbo;

            virtual void draw(const UIElement& e);

            static void initialize();
            static void terminate();


            UIRenderer();
            virtual ~UIRenderer();

    };


} // undicht

#endif // UI_RENDERER_H
