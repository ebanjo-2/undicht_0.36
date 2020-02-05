#include "font.h"
#include <core/event_logger.h>
#include <core/string_tools.h>

namespace undicht {

    using namespace core;


    FontCharacter empty_char;

    Font::Font() {
        //ctor

        m_font_map.setName("font_map");

    }

    Font::~Font() {
        //dtor
    }

    const FontCharacter& Font::getChar(int id) {

        for(const FontCharacter& f : m_chars) {

            if(f.m_char_id == id) {

                return f;
            }
        }

        EventLogger::storeNote(Note(UND_ERROR, "FONT:ERROR: failed to return char " + toStr((char)id), UND_CODE_ORIGIN));

        return empty_char;
    }


} // undicht
