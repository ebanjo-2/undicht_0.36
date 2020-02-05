#ifndef IMAGE_READER_H_INCLUDED
#define IMAGE_READER_H_INCLUDED

#include <graphics/texture.h>
#include <2D/animation.h>
#include <file_loading/file_reader.h>

// a reader that can load image files (.jpg, .png, ... ) to textures

namespace undicht {


    class ImageReader {
            /** a reader that can load image files (.jpg, .png, ... ) to textures */
        public:



            /** loads the content of the file to the texture */
            void loadImage(graphics::Texture& texture, std::string file_name);

            void loadAnimation(Animation2D& anim, std::string file_name);

        private:
            // loading animation files

            void getTextureNames(std::vector<std::string>& textures, std::vector<float>& switch_times, FileReader& reader);

            /** @return the duration of the animation */
            float getDuration(FileReader& reader);

    };


} // undicht



#endif // IMAGE_READER_H_INCLUDED
