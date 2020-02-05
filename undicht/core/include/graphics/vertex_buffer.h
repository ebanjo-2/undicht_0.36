#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <core/shared_lib_class.h>
#include <core/buffer_layout.h>
#include <vector>


namespace undicht {

    namespace graphics {

        SHARED_LIB_DECL_BASE_CLASS(VertexBuffer, VertexBufferBase, createVertexBuffer, copyVertexBuffer, deleteVertexBuffer);


        SHARED_LIB_CLASS(class VertexBuffer : public VertexBufferBase {
                /** a class that can hold multiple vertices which can be used to build meshes */
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

        };)

    } // graphics

} // undicht

#endif // VERTEX_BUFFER_H
