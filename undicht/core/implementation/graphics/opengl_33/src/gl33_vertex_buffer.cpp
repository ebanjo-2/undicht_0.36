#include <glad/glad.h>

#include "gl33_vertex_buffer.h"
#include <core/shared_lib.h>
#include <core/event_logger.h>
#include "gl_tools.h"
#include <iostream>

// decided not to use the good old abstraction (core) from the previous attempts of undicht, but to write opengl code directly
// into the implementation of the api

using namespace undicht::core;


namespace undicht {

    namespace graphics {

        namespace gl33 {

            unsigned int bound_vao = 0;


            VertexBuffer::VertexBuffer() {
                //ctor

                unsigned int temp_vbo;
                unsigned int temp_vao;

                glGenBuffers(1, &temp_vbo);
                glGenVertexArrays(1, &temp_vao);

                m_vbo_id.setID(temp_vbo);
                m_vao_id.setID(temp_vao);

                bind();
            }

            VertexBuffer::~VertexBuffer() {

                if(m_vbo_id.removeUser()){
                    glDeleteBuffers(1, &m_vbo_id.m_id);
                }

                if(m_vao_id.removeUser()){
                    glDeleteVertexArrays(1, &m_vao_id.m_id);
                }

            }

            void VertexBuffer::setData(const std::vector<float>& data, unsigned int offset) {

                setData(data.data(), data.size() * sizeof(float), offset);

            }

            void VertexBuffer::setData(const void* data, unsigned int size, unsigned int offset) {

                // testing if resize is needed
                if(offset + size > getSize()) {
                    resize(offset + size);
                }

                bind();
                glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

                undCheckGLError(UND_CODE_ORIGIN);

            }

            void VertexBuffer::setLayout(const core::BufferLayout& layout) {

                m_layout = layout;

                // telling opengl about the layout via attribute pointers
                int vertex_size = getVertexSize();
                int attr_id = 0;
                int attr_sum = 0;

                bind();


                for(const int& attr : layout.m_types) {
                    if(attr == UND_FLOAT) {

                        glVertexAttribPointer(attr_id, 1, GL_FLOAT, GL_FALSE, vertex_size, (void*)attr_sum); // will always produce a warning
                        glEnableVertexAttribArray(attr_id);
                        attr_sum += sizeof(float);
                    } else if( attr == UND_INT) {

                        glVertexAttribPointer(attr_id, 1, GL_INT, GL_FALSE, vertex_size, (void*)attr_sum); // will always produce a warning
                        glEnableVertexAttribArray(attr_id);
                        attr_sum += sizeof(int);
                    } else if( attr == UND_VEC3F) {

                        //std::cout << "setting vec3 attribute, id= " << attr_id << "\n";

                        glVertexAttribPointer(attr_id, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)attr_sum); // will always produce a warning
                        glEnableVertexAttribArray(attr_id);
                        attr_sum += 3 * sizeof(float);
                    } else if( attr == UND_VEC2F) {

                        //std::cout << "setting vec2 attribute, id= " << attr_id << "\n";

                        glVertexAttribPointer(attr_id, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)attr_sum); // will always produce a warning
                        glEnableVertexAttribArray(attr_id);
                        attr_sum += 2 * sizeof(float);
                    } else if( attr == UND_MAT4F) {
                        glVertexAttribPointer(attr_id, 16, GL_FLOAT, GL_FALSE, vertex_size, (void*)attr_sum); // will always produce a warning
                        glEnableVertexAttribArray(attr_id);
                        attr_sum += 16 * sizeof(float);
                    }

                    attr_id++;
                }

                undCheckGLError(UND_CODE_ORIGIN);
            }

            void VertexBuffer::getData(std::vector<float>& data, unsigned int num_floats, unsigned int offset) {

                undCheckGLError(UND_CODE_ORIGIN);
            }

            void VertexBuffer::getData(void* data, unsigned int size, unsigned int offset) {
                /// data should have at least #size bytes reserved

                undCheckGLError(UND_CODE_ORIGIN);
            }

            unsigned int VertexBuffer::getSize() {
                /// returns the number of bytes stored in the buffer

                return m_size;
            }

            unsigned int VertexBuffer::getVertexSize() {
                /// returns the size of one vertex

                return m_layout.getTotalSize();
            }


            const core::BufferLayout& VertexBuffer::getLayout() {
                /// returns the layout of the stored data

                return m_layout;
            }

            /// non api functions ///

            void VertexBuffer::resize(unsigned int size) { // taken and modified from the old opengl abstraction
                /**@param the size is in bytes */
                /**@brief reserves buffer memory by calling setData()
                * old data does not get moved */


                // saving the data
                unsigned char* old_data = new unsigned char[getSize()];
                unsigned int old_data_size = getSize();

                getData(old_data, getSize(), 0 );

                // resizing the buffer and restoring the data
                if(getSize() < size) {
                    // increasing the size of the buffer (old_data not big enough)

                    bind();
                    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, old_data_size, old_data);

                } else {
                    // decreasing the size of the buffer (old_data big enough)

                    bind();
                    glBufferData(GL_ARRAY_BUFFER, size, old_data, GL_STATIC_DRAW);
                }

                m_size = size;
                delete[] old_data;

                undCheckGLError(UND_CODE_ORIGIN);
            }

            void VertexBuffer::bind() {

                if(bound_vao != m_vao_id) {

                    glBindVertexArray(m_vao_id);
                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
                    bound_vao = m_vao_id;

                }

            }



            SHARED_LIB_EXPORT implementation::VertexBuffer* createVertexBuffer() {

                return new gl33::VertexBuffer;
            }


            SHARED_LIB_EXPORT void copyVertexBuffer(implementation::VertexBuffer* c, implementation::VertexBuffer* o) {
                // to be done properly
                VertexBuffer* c_vertex_buffer = (VertexBuffer*)c;

                if(c_vertex_buffer->m_vbo_id.removeUser()){
                    glDeleteBuffers(1, &c_vertex_buffer->m_vbo_id.m_id);
                }

                if(c_vertex_buffer->m_vao_id.removeUser()){
                    glDeleteVertexArrays(1, &c_vertex_buffer->m_vao_id.m_id);
                }

                *c_vertex_buffer = *(VertexBuffer*)o;
            }

            SHARED_LIB_EXPORT void deleteVertexBuffer(implementation::VertexBuffer* vertex_buffer) {

                delete vertex_buffer;
            }



        } // gl33

    } // graphics

} //undicht

