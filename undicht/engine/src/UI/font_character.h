#ifndef FONT_CHARACTER_H
#define FONT_CHARACTER_H


namespace undicht {

    class FontCharacter {
        /** a class storing the data about a single character of a font (at font size 1) */
        public:

            int m_char_id = 0;

            // the position (top left) of the character on the font map (range: 0-1)
            float m_font_map_x = 0.0f;
            float m_font_map_y = 0.0f;

            // the size of the character on the font map (range: 0-1)
            // and the character getting drawn (the font this character is part of determines an extra scalar)
            float m_width = 0.0f;
            float m_height = 0.0f;

            // how the characters position should be offset when rendering a line of text
            float m_offset_x = 0.0f;
            float m_offset_y = 0.0f;

            // how far the cursor should advance after the character has been drawn
            float m_cursor_advance = 0.0f;

            float m_line_height = 0.0f;


            FontCharacter();
            virtual ~FontCharacter();
    };

} // undicht

#endif // FONT_CHARACTER_H
