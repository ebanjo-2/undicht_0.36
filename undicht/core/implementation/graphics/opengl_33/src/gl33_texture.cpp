#include "gl33_texture.h"
#include <glad/glad.h>
#include <array>
#include <core/types.h>
#include "gl_tools.h"

using namespace undicht::core;

namespace undicht {

    namespace graphics {

        namespace gl33 {

            std::array<int,16> bound_textures;

            Texture::Texture() {

                glGenTextures(1, &m_id.m_id);

            }

            Texture::~Texture() {

                if(m_id.removeUser()) {
                    glDeleteTextures(1, &m_id.m_id);
                }

            }

            //////////////////////////////////////// managing the textures format /////////////////////////////////////

            void Texture::setPixelFormat(const core::BufferLayout& format) {

                std::array<int,4> component_types = getComponentTypes(format); // the types of each color component
                setOpenglFormat(component_types);


            }


            void Texture::setSize(int width, int height, int depth) {

                m_width = width;
                m_height = height;
                m_depth = depth;

                m_size_set = true;
                updateFormat();

            }


            void Texture::getSize(int& width, int& height) {

                width = m_width;
                height = m_height;

            }

            void Texture::getSize(int& width, int& height, int& depth) {

                width = m_width;
                height = m_height;
                depth = m_depth;

            }

            void Texture::setUsesMipMap(bool use_mip_map) {

                // if the mipmap was generated it will be used

            }

            ///////////////////////////////////////// managing the textures data //////////////////////////////////////////


            void Texture::setData(char* data, int byte_size, int depth, int mip_map_level, int offset) {

                if(!(m_size_set && m_layout_set)) {
                    EventLogger::storeNote(Note(UND_ERROR, "Texture: cant set data, format incomplete", UND_CODE_ORIGIN));
                    return;
                }

                glBindTexture(m_type, m_id);

                if(m_type == GL_TEXTURE_2D) {

                    glTexImage2D(m_type, 0, m_memory_format, m_width, m_height, 0, m_pixel_layout, GL_UNSIGNED_BYTE, data);
                    //glTexSubImage2D(m_type, mip_map_level, offset, 0, m_width, m_height, m_memory_format, GL_UNSIGNED_BYTE, data);

                } else if (m_type == GL_TEXTURE_2D_ARRAY) {

                    glTexSubImage3D(m_type, 0, 0, 0, depth, m_width, m_height, 1, m_pixel_layout, GL_UNSIGNED_BYTE, data);


                }

                undCheckGLError(UND_CODE_ORIGIN);



            }


            void Texture::generateMipMaps() {

                glBindTexture(m_type, m_id);
                glGenerateMipmap(m_type);

            }

            ////////////////////////////////// managing the access of the texture data in a shader/////////////////////////////////////

            void Texture::setName(const std::string& name) {

                m_name = name;

            }

            ////////////////////////////////// opengl only functions //////////////////////////////////




            void Texture::bind(int target) {

                if(target >= bound_textures.size()) {
                    EventLogger::storeNote(Note(UND_ERROR, "TEXTURE:ERROR: failed to bind texture, target exceeds limit", UND_CODE_ORIGIN));
                    return;
                }

                if(bound_textures[target] != m_id) {

                    glActiveTexture(GL_TEXTURE0 + target);
                    glBindTexture(m_type, m_id);
                    bound_textures[target] = m_id;

                }

            }


            /** updates the texture to the set layout and size */
            void Texture::updateFormat() {

                if(m_size_set && m_layout_set) {

                    if(m_depth == 1) {
                        // 2D texture

                        m_type = GL_TEXTURE_2D;
                        glBindTexture(m_type, m_id);
                        glTexImage2D(GL_TEXTURE_2D, 0, m_memory_format, m_width, m_height, 0, m_pixel_layout, GL_UNSIGNED_BYTE, NULL);

                    } else {
                        // texture array / 3d texture / cubemap

                        m_type = GL_TEXTURE_2D_ARRAY;
                        glBindTexture(m_type, m_id);

                        // glTexStorage3D(m_type, 1, m_memory_format, m_width, m_height, m_depth); // might require opengl 4.2 or higher
                        glTexImage3D(m_type, 0, m_memory_format, m_width, m_height, m_depth, 0, m_pixel_layout, GL_UNSIGNED_BYTE, 0);

                    }

                    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(m_type, GL_TEXTURE_WRAP_R, GL_REPEAT);

                    glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    undCheckGLError(UND_CODE_ORIGIN);

                }

            }

            /** @return an array containing the type for each component of the color */
            std::array<int,4> Texture::getComponentTypes(const core::BufferLayout& format) {

                int component_count = 0;
                std::array<int,4> component_types; // the types of each color component

                // initializing all without a type
                for(int& i : component_types)
                    i = UND_TYPE_UNAVAILABLE;

                for(const int& component : format.m_types) {


                    if(component == UND_VEC3F) { // 3 floats
                        component_types[component_count + 0] = UND_FLOAT;
                        component_types[component_count + 1] = UND_FLOAT;
                        component_types[component_count + 2] = UND_FLOAT;
                        component_count += 3;
                    } else if(component == UND_VEC2F) { // 2 floats
                        component_types[component_count + 0] = UND_FLOAT;
                        component_types[component_count + 1] = UND_FLOAT;
                        component_count += 2;
                    } else {
                        // types defining one component

                        component_types[component_count] = component;
                        component_count++;
                    }
                }

                return component_types;
            }

            void Texture::setOpenglFormat(const std::array<int,4>& component_types) {

                if(component_types[0] == UND_UNSIGNED_CHAR) {
                    if(component_types[1] == UND_UNSIGNED_CHAR) {
                        if(component_types[2] == UND_UNSIGNED_CHAR) {
                            if(component_types[3] == UND_UNSIGNED_CHAR) {
                                // 32 bit rgba
                                m_pixel_layout = GL_RGBA;
                                m_memory_format = GL_RGBA8;
                            } else if (component_types[3] == UND_TYPE_UNAVAILABLE) {
                                // 24 bit rgb
                                m_pixel_layout = GL_RGB;
                                m_memory_format = GL_RGB8;
                            }
                        }
                    }
                } else if(component_types[0] == UND_FLOAT) {
                    // dunno what to do
                }

                m_layout_set = true;
                updateFormat();

            }

            void Texture::setOpenglFormat(int layout, int memory_format) {

                m_pixel_layout = layout;
                m_memory_format = memory_format;

                m_layout_set = true;
                updateFormat();
            }

            //////////////////// functions to load a texture object from the shared lib  ////////////////////////////////////

            SHARED_LIB_EXPORT implementation::Texture*createTexture() {
                return new gl33::Texture;
            }

            SHARED_LIB_EXPORT void copyTexture(implementation::Texture* c, implementation::Texture* o) {

                Texture* c_texture = (Texture*)c;

                if(c_texture->m_id.removeUser()) {
                    glDeleteTextures(1, &c_texture->m_id.m_id);
                }

                *c_texture = *(Texture*)o;
            }

            SHARED_LIB_EXPORT void deleteTexture(implementation::Texture* object) {
                delete (Texture*)object;
            }


        } // gl33

    } // graphics

} // undicht
