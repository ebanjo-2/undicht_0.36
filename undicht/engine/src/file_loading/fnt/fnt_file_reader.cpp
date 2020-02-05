#include "fnt_file_reader.h"
#include <string.h>
#include <core/event_logger.h>
#include <file_loading/image/image_reader.h>

namespace undicht {

    using namespace core;

    FntFileReader::FntFileReader() {
        //ctor
    }

    FntFileReader::FntFileReader(std::string file) {
        open(file);
    }

    FntFileReader::~FntFileReader() {
        //dtor
    }



    void FntFileReader::loadFont(Font& loadTo) {


        loadFontMap(loadTo.m_font_map);

        int font_map_width, font_map_height;
        loadTo.m_font_map.getSize(font_map_width, font_map_height);

        // loading the line height
        float line_height = 0.0f;
        std::string line;
        size_t pos;
        reset();
        while(!eof()) {

            getLine(line);

            pos = line.find("lineHeight=");

            if(pos != std::string::npos) {

                line_height = float(getInt(line.substr(pos), "lineHeight=")) / font_map_height;
                std::cout << "line height: " << line_height << "\n";
                break;
            }

        }

        reset();

        while(!eof()) {

            loadTo.m_chars.push_back(FontCharacter());
            loadNextChar(loadTo.m_chars.back(), font_map_width, font_map_height);

            loadTo.m_chars.back().m_line_height = line_height;

        }

    }

    /////////////////////////////////// functions to load parts of the font /////////////////////////////////////

    void FntFileReader::loadFontMap(graphics::Texture& loadTo) {
        // file name is declared after "file="

        std::string line;
        std::string file_name;

        size_t start_pos = std::string::npos;

        reset();

        while(!eof()) {

            getLine(line);
            start_pos = line.find("file=");

            if(start_pos != std::string::npos) {

                file_name = line.substr(start_pos + 6); // the file name should be the last part of the line
                size_t end_pos = file_name.rfind('"'); // removing the " at the end
                file_name.resize(end_pos);
            }

        }

        if(!file_name.size()) {

            EventLogger::storeNote(Note(UND_ERROR, "ERROR: failed to load font map for font " + m_file_name, UND_CODE_ORIGIN));
            return;
        }

        ImageReader image_reader;
        image_reader.loadImage(loadTo, getFilePath(m_file_name) + file_name);

    }


    void FntFileReader::loadNextChar(FontCharacter& loadTo, int font_map_width, int font_map_height) {
        // every character declaration starts with "char id="

        std::string line;

        while(!eof()) {

            getLine(line);

            if (!line.compare(0, 8, "char id=")) {

                loadTo.m_char_id = getInt(line, "char id=");

                loadTo.m_font_map_x = float(getInt(line, "x=")) / font_map_width;
                loadTo.m_font_map_y = float(getInt(line, "y=")) / font_map_height;

                loadTo.m_width = float(getInt(line, "width=")) / font_map_width;
                loadTo.m_height = float(getInt(line, "height=")) / font_map_height;

                loadTo.m_offset_x = float(getInt(line, "xoffset=")) / font_map_width;
                loadTo.m_offset_y = float(getInt(line, "yoffset=")) / font_map_height;

                loadTo.m_cursor_advance = float(getInt(line, "xadvance=")) / font_map_width;

                // fixing the way the uv gets stored in .fnt files
                loadTo.m_font_map_y = 1 - (loadTo.m_font_map_y + loadTo.m_height);
                loadTo.m_offset_x *= -2;    // there probably is something wrong with how the characters get placed
                loadTo.m_offset_y *= -0.5;  // these values were chosen cause it made the text look better
                loadTo.m_cursor_advance *= 0.8;

                break; // only loading one char
            }


        }

    }


    int FntFileReader::getInt(const std::string& source, const std::string& string_before_int) {
        /** @return the int following the string_before_int in the source string */

        size_t int_start = source.find(string_before_int) + string_before_int.size();

        return stoi(source.substr(int_start));
    }


} // undicht
