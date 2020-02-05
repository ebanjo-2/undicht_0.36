#ifndef FONT_H
#define FONT_H

#include "font_character.h"
#include <vector>
#include <graphics/texture.h>


namespace undicht {

    class Font {
        public:

            graphics::Texture m_font_map;

            std::vector<FontCharacter> m_chars;

            // how the characters dimensions should be scaled for a font size of 1
            float m_scale = 0.0f;

            const FontCharacter& getChar(int id);

            Font();
            virtual ~Font();

    };

} // undicht

#endif // FONT_H
