#include "ui_demo.h"
#include <file_loading/fnt/fnt_file_reader.h>
#include <core/string_tools.h>


namespace undicht {


    UIDemo::UIDemo(undicht::window::Window* window) {

        m_key_input.setWindow(window);
        m_mouse_input.setWindow(window);

        m_ui_master.addUIElement(&m_button);
        m_ui_master.addUIElement(&m_button_2);


        FntFileReader fnt_reader("res/fonts/sans/sans.fnt");
        fnt_reader.loadFont(m_font);

        m_button.setPosition(glm::vec2(0.0,0.0));
        m_button.setSize(glm::vec2(0.6, 0.6));
        m_button.setCaption(Label("hello world", m_font));
        m_button.m_caption.setColor(glm::vec4(1,1,1, 0.9));
        m_button.m_caption.setEdgeColor(glm::vec4(1));


        m_button_2.setPosition(glm::vec2(-0.8,0.8));
        m_button_2.setSize(glm::vec2(0.2, 0.2));
        m_button_2.setCaption(Label("hello world 2", m_font));
        m_button_2.m_caption.setColor(glm::vec4(1,1,1, 0.9));
        m_button.m_caption.setEdgeColor(glm::vec4(1));



    }

    UIDemo::~UIDemo () {

    }


    void UIDemo::update() {

        m_key_input.updateChangedKeys();
        m_mouse_input.updateChangedButtons();

        m_ui_master.forwardInput(m_key_input, m_mouse_input);

    }


    void UIDemo::draw() {

        m_renderer.draw(m_button);
        m_renderer.draw(m_button_2);

    }


} // undicht
