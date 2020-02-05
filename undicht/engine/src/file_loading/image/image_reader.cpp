// the implementation of the image loader using the stb image library

#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include "stb/stb_image.h"

#include "image_reader.h"
#include <iostream>
#include "file_loading/file_reader.h"
#include <core/buffer_layout.h>

using namespace undicht::graphics;
using namespace undicht::core;

namespace undicht {

    // the filename extensions to get the cubemap texture files
    const std::vector<std::string> cube_map_faces({"_rt", "_ft", "_lf", "_bk", "_up", "_dn"});



    void ImageReader::loadImage(Texture& texture, std::string file_name) {
        /** loads the content of the file to the texture */

        stbi_set_flip_vertically_on_load(true);


        int nr_channels; // havent found a use for this jet, its not stored in the texture
        int width;
        int height;

        //loading the image data
        unsigned char* data = stbi_load(file_name.data(), &width, &height, &nr_channels, STBI_rgb_alpha);

        if(data) { //testing whether the image could be loaded or not

            BufferLayout pixel_layout({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR});
            texture.setPixelFormat(pixel_layout);
            texture.setSize(width, height);

            //loading the data to the texture
            texture.setData((char*)data, width * height * 4);

        } else {

            std::cout << "CORE:TEXTURE:ERROR: failed to read image: " << file_name << std::endl;

        }

        stbi_image_free(data);


    }

    void ImageReader::loadAnimation(Animation2D& anim, std::string file_name) {

        // expecting a .txt file saying what textures need to loaded
        FileReader reader(file_name);

        std::vector<std::string> texture_names;
        getTextureNames(texture_names, anim.m_times, reader);

        // loading the duration of the animation
        anim.m_duration = getDuration(reader);

        std::cout << "animation duration: " << anim.m_duration << "\n";


        // loading the textures
        stbi_set_flip_vertically_on_load(true);

        int nr_channels; // havent found a use for this jet, its not stored in the texture
        int width;
        int height;
        bool size_set = false;

        for(int i = 0; i < texture_names.size(); i++) {

            std::string texture_file = getFilePath(file_name) + texture_names.at(i);


            //loading the image data
            unsigned char* data = stbi_load(texture_file.data(), &width, &height, &nr_channels, STBI_rgb_alpha);


            if(data) { // testing whether the image could be loaded or not

                if(!size_set) {
                    BufferLayout pixel_layout({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR});
                    anim.m_texture_source.setPixelFormat(pixel_layout);
                    anim.m_texture_source.setSize(width, height, texture_names.size());
                    size_set = true;

                }


                // loading the data to the texture
                anim.m_texture_source.setData((char*)data, width * height * 4, i);

            } else {

                std::cout << "CORE:TEXTURE:ERROR: failed to read image: " << texture_file << "t" << std::endl;

            }

            stbi_image_free(data);

        }
    }

    void ImageReader::getTextureNames(std::vector<std::string>& textures, std::vector<float>& switch_times, FileReader& reader) {

        int first_frame; // frames describe a state of a sprite animation with a texture and a time of when to switch to it
        reader.countLines("frame", first_frame);

        reader.setPosition(first_frame);


        // loading the frame textures
        std::string line;
        int old_position = -1;
        while(!reader.eof()) {

            old_position = reader.getPosition(); // the reader wont move once it reaches the last *frame*
            reader.getLine(line, "frame"); // frame lines have to have no free ones in between
            if(old_position == reader.getPosition()) // no new frame line
                break;

            // loading the start time of the frame
            int time_start, time_end;
            time_start = line.find(' ');
            time_end = line.find(' ', time_start + 1);
            switch_times.push_back(strtof(line.data() + time_start, NULL));

            // loading the source file for the texture
            textures.push_back(line.substr(time_end + 1));

            if((textures.back().back() == '\n') || (textures.back().back() == '\r')) {
                textures.back().pop_back();
            }

            std::cout << "time to switch to texture " << textures.back() << ": " << switch_times.back() << "\n";
        }

    }


    float ImageReader::getDuration(FileReader& reader) {
        /** @return the duration of the animation */

        reader.reset();
        int duration_line;
        std::string line;

        reader.countLines("duration", duration_line);

        reader.setPosition(duration_line);
        reader.getLine(line);

        return strtof(line.data() + line.find(' '), NULL);
    }


} // undicht
