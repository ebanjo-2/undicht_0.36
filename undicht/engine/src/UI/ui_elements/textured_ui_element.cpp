#include "textured_ui_element.h"

#include <window/key_ids.h>


namespace undicht {


    using namespace window;
    using namespace core;

    TexturedUIElement::TexturedUIElement() {
        //ctor

        unsigned char color[] = {0,0,0,0};

        m_texture.setName("color");
        m_texture.setPixelFormat(std::vector<int>({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR}));
        m_texture.setSize(1,1);
        m_texture.setData((char*)color, sizeof(color));
        m_type = UND_UI_TEXTURED_ELEMENT;
    }

    TexturedUIElement::~TexturedUIElement() {
        //dtor
    }

    const graphics::Texture& TexturedUIElement::getTexture() const {

        return m_texture;
    }

    bool TexturedUIElement::onKeyPress(int key_id, int key_state) {

    }

} // undicht
