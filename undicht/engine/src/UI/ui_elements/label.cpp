#include "label.h"
#include <core/types.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>


namespace undicht {

    using namespace graphics;
    using namespace core;

    Label::Label() {
        //ctor

        m_type = UND_UI_TEXT;
        m_text_data.setName("text_data");
        m_font_size.setName("font_size");
        m_color.setName("color");
        m_edge_color.setName("edge_color");

        setFontSize(1.2);
    }

    Label::Label(const std::string& caption, const Font& font) {

        m_type = UND_UI_TEXT;
        m_text_data.setName("text_data");
        m_font_size.setName("font_size");
        m_color.setName("color");
        m_edge_color.setName("edge_color");

        setFont(font);
        setCaption(caption);

        setFontSize(1.2);
    }


    Label::~Label() {
        //dtor
    }

    void Label::setColor(const glm::vec4& color) {

        m_color.setData(glm::value_ptr(color), UND_VEC4F);
    }

    const graphics::Uniform& Label::getColor() {

        return m_color;
    }


    void Label::setEdgeColor(const glm::vec4& color) {

        m_edge_color.setData(glm::value_ptr(color), UND_VEC4F);
    }

    const graphics::Uniform& Label::getEdgeColor() {

        return m_edge_color;
    }


    void Label::setFont(const Font& font) {

        if(&font != m_font) {
            m_font = (Font*)&font;
            buildTextData();
        }
    }

    const Font& Label::getFont() const{

        return *m_font;
    }


    void Label::setFontSize(float size) {

        m_font_size.setData(&size, UND_FLOAT);
        buildTextData();

    }


    void Label::setCaption(const std::string& caption) {

        if(m_caption.compare(caption)) {
            m_caption = caption;
            buildTextData();
        }
    }

    const std::string& Label::getCaption() const{

        return m_caption;
    }


    //////////////////////////////////////////// functions returning data to render the text ///////////////////////////

    const Uniform& Label::getTextData() {
        /** @return a uniform (buffer) with all the data needed to draw the characters from the font map */

        return m_text_data;
    }

    int Label::getCharCount() {
        /** @return the number of characters in the caption of the label */

        return m_caption.size();
    }

    const Uniform& Label::getFontSize() {

        return m_font_size;
    }

    void Label::buildTextData() {

        if((!m_font) || (!getCharCount())) {

            return;
        }

        float total_x_advance = 0; // the total x advance of the "cursor"
        float total_y_advance = 0;

        // 8 floats: vec2 uv_top_left, vec2 uv_size, vec2 offset, vec2 cursor
        float* text_data = new float[8 * getCharCount()];

        int chars_processed = 0;

        // building the text data
        for(char& c : m_caption) {

            const FontCharacter& char_data = m_font->getChar(c);

            // uv top left
            text_data[chars_processed * 8 + 0] = char_data.m_font_map_x;
            text_data[chars_processed * 8 + 1] = char_data.m_font_map_y;
            // uv size
            text_data[chars_processed * 8 + 2] = char_data.m_width;
            text_data[chars_processed * 8 + 3] = char_data.m_height;
            // offset + cursor
            text_data[chars_processed * 8 + 4] = char_data.m_offset_x + total_x_advance;
            text_data[chars_processed * 8 + 5] = char_data.m_offset_y + total_y_advance;
            // char size
            text_data[chars_processed * 8 + 6] = char_data.m_width;
            text_data[chars_processed * 8 + 7] = char_data.m_height;

            // moving the cursor
            total_x_advance += char_data.m_cursor_advance;

            chars_processed++;
        }

        // storing the data in the uniform buffer
        BufferLayout layout({UND_VEC4F, UND_VEC4F});
        m_text_data.setData(text_data, layout, getCharCount());

    }

} // undicht
