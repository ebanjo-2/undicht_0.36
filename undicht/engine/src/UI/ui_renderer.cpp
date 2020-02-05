#include "ui_renderer.h"
#include <file_loading/file_reader.h>
#include <core/buffer_layout.h>
#include <core/types.h>
#include <string>

#include <UI/ui_elements/textured_ui_element.h>
#include <UI/ui_elements/label.h>

#include <glm/glm/gtc/type_ptr.hpp>

#include <core/event_logger.h>


namespace undicht {

    using namespace graphics;
    using namespace core;

    const float quad_vertices[] = { -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f,  0.5f}; // a quad with a width and height of 1
    const core::BufferLayout quad_vbo_layout = core::BufferLayout({core::UND_VEC2F});

    graphics::Shader* UIRenderer::s_textured_element_shader = 0;
    graphics::Shader* UIRenderer::s_text_shader = 0;
    graphics::VertexBuffer* UIRenderer::s_quad_vbo = 0;

    UIRenderer::UIRenderer() {

        m_position_uniform.setName("position");
        m_scale_uniform.setName("scale");


    }

    UIRenderer::~UIRenderer() {
        //dtor
    }


    void UIRenderer::initialize() {


        s_textured_element_shader = new Shader;
        s_text_shader = new Shader;
        s_quad_vbo = new VertexBuffer;

        // loading the shader source
        std::string file_path = getFilePath(replaceAll(UND_CODE_SRC_FILE, (char)92, '/')) + "shader/textured_element.txt";
        std::string source_buffer;

        FileReader reader(file_path);
        s_textured_element_shader->loadSource(reader.getAll(source_buffer));

        file_path = getFilePath(replaceAll(UND_CODE_SRC_FILE, (char)92, '/')) + "shader/text.txt";

        reader.open(file_path);
        s_text_shader->loadSource(reader.getAll(source_buffer));

        s_quad_vbo->setData(quad_vertices, 2 * 6 * sizeof(float));
        s_quad_vbo->setLayout(quad_vbo_layout);
    }

    void UIRenderer::terminate() {

        delete s_quad_vbo;
        delete s_text_shader;
        delete s_textured_element_shader;
    }



    void UIRenderer::draw(const UIElement& e) {

        // drawing the element
        Renderer::enableDepthTest(false);
        Renderer::enableBackFaceCulling(false);



        if(e.getType() == UND_UI_TEXTURED_ELEMENT) {
            // using the sprite rendering shader

            const TexturedUIElement& textured_element = (const TexturedUIElement&)e;

            m_position_uniform.setData(glm::value_ptr(e.getPositionOnScreen()), UND_VEC2F);
            m_scale_uniform.setData(glm::value_ptr(e.getSizeOnScreen()), UND_VEC2F);

            s_textured_element_shader->loadUniform(m_position_uniform);
            s_textured_element_shader->loadUniform(m_scale_uniform);
            s_textured_element_shader->loadTexture(textured_element.getTexture());
            submit(s_textured_element_shader);
            submit(s_quad_vbo);

            ((Renderer*)this)->draw();


        } else if (e.getType() == UND_UI_TEXT) {

            Label& label = *((Label*)&e);

            m_position_uniform.setData(glm::value_ptr(e.getPositionOnScreen()), UND_VEC2F);
            m_scale_uniform.setData(glm::value_ptr(e.getSizeOnScreen()), UND_VEC2F);

            s_text_shader->loadUniform(label.getFontSize());
            s_text_shader->loadUniform(label.getTextData());
            s_text_shader->loadUniform(label.getColor());
            s_text_shader->loadUniform(label.getEdgeColor());

            s_text_shader->loadUniform(m_position_uniform);
            s_text_shader->loadUniform(m_scale_uniform);
            s_text_shader->loadTexture(label.getFont().m_font_map);


            submit(s_text_shader);
            submit(s_quad_vbo);

            ((Renderer*)this)->draw(label.getCharCount());

        }


        // drawing its children (until this reaches an element with no children)
        for(const UIElement* child : e.m_child_elements) {

            draw(*child);
        }

    }

} // undicht
