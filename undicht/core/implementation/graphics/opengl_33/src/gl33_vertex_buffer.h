#ifndef GL33_VERTEX_BUFFER_H
#define GL33_VERTEX_BUFFER_H

#include <graphics/vertex_buffer.h>
#include <core/buffer_layout.h>
#include <core/shared_id.h>


namespace undicht {

    namespace graphics {

        namespace gl33 {

            class VertexBuffer : public implementation::VertexBuffer  {
                public:
                    // data & non api functions

                    core::SharedID m_vbo_id = 0;
                    core::SharedID m_vao_id = 0;
                    unsigned int m_size = 0;

                    core::BufferLayout m_layout;

                    void resize(unsigned int size);

                    void bind();


                public:

                    virtual void setData(const std::vector<float>& data, unsigned int offset = 0);
                    virtual void setData(const void* data, unsigned int size, unsigned int offset = 0);

                    virtual void setLayout(const core::BufferLayout& layout);

                    virtual void getData(std::vector<float>& data, unsigned int num_floats, unsigned int offset = 0);
                    virtual void getData(void* data, unsigned int size, unsigned int offset = 0); /// data should have at least #size bytes reserved

                    virtual unsigned int getSize(); /// returns the number of bytes stored in the buffer
                    virtual unsigned int getVertexSize(); /// returns the size of one vertex
                    virtual const core::BufferLayout& getLayout(); /// returns the layout of the stored data


                    VertexBuffer();
                    virtual ~VertexBuffer();

            };

        } // gl33

    } // graphics

} // undicht

#endif // GL33_VERTEX_BUFFER_H
