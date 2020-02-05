#ifndef FNT_FILE_READER_H
#define FNT_FILE_READER_H


#include <file_loading/file_reader.h>
#include <UI/font.h>


namespace undicht {


    class FntFileReader : public FileReader {
        /** a file reader to read (kind of outdated) .fnt files */


        public:

            virtual void loadFont(Font& loadTo);

            FntFileReader();
            FntFileReader(std::string file);
            virtual ~FntFileReader();

        private:

            virtual void loadFontMap(graphics::Texture& loadTo);
            virtual void loadNextChar(FontCharacter& loadTo, int font_map_width, int font_map_height);

            /** @return the int following the string_before_int in the source string
            * @return 0 if the int / string was not found */
            int getInt(const std::string& source, const std::string& string_before_int);


    };


} // undicht

#endif // FNT_FILE_READER_H
