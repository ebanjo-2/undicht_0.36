#include <graphics/texture.h>

namespace undicht {

    namespace graphics {

        SHARED_LIB_DEF_BASE_CLASS( Texture, createTexture, copyTexture, deleteTexture);

        //////////////////////////////////////// managing the textures format /////////////////////////////////////

        SHARED_LIB_API_IMPL(void Texture::setPixelFormat(const core::BufferLayout& format)) {
            /** determines the size and layout of a single pixel (i.e. UND_VEC4F for RGBA) */

            m_shared_lib_object->setPixelFormat(format);
        }


        SHARED_LIB_API_IMPL(void Texture::setSize(int width, int height, int depth)) {
            /** @param depth: a texture object may contain multiple 2D textures, like in an array
            * this can be used to store data for a cubemap (with depth = 6) */

            m_shared_lib_object->setSize(width, height, depth);
        }

        SHARED_LIB_API_IMPL(void Texture::getSize(int& width, int& height)) {

            m_shared_lib_object->getSize(width, height);
        }

        SHARED_LIB_API_IMPL(void Texture::getSize(int& width, int& height, int& depth)) {

            m_shared_lib_object->getSize(width, height, depth);
        }


        SHARED_LIB_API_IMPL(void Texture::setUsesMipMap(bool use_mip_map)) {
            /** sets whether there should be a mipmap for this texture
            * may speed up the scaling of the texture, i.e. when applied to a 3d object
            * but also uses more vram, so dont use it if u dont want to scale the texture */

            m_shared_lib_object->setUsesMipMap(use_mip_map);
        }

        ///////////////////////////////////////// managing the textures data //////////////////////////////////////////


        SHARED_LIB_API_IMPL(void Texture::setData(char* data, int byte_size, int depth, int mip_map_level, int offset)) {
            /** stores pixel data for the texture
            * @param data: should contain pixels in the set Pixel Format
            * @param byte_size: the size of the data to store
            * @param depth: for which depth level the data should be set
            * @param mip_map_level: for which mip map level the data should be (with 0 being the biggest/default, 1 being half the size of 0 and so on)
            * @param offset (in bytes): if you dont want to start at the first pixel */

            m_shared_lib_object->setData(data, byte_size, depth, mip_map_level, offset);
        }


        SHARED_LIB_API_IMPL(void Texture::generateMipMaps()) {
            /** will automatically generate a mipmap for the textures set data */

            m_shared_lib_object->generateMipMaps();
        }

        ////////////////////////////////// managing the access of the texture data in a shader/////////////////////////////////////


        SHARED_LIB_API_IMPL(void Texture::setName(const std::string& name)) {
            /** binds the texture to the variable in a shader with that name
            * so that the textures data can be accessed through that variable */

            m_shared_lib_object->setName(name);
        }

    } // graphics

} // undicht
