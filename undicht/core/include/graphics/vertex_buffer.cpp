#include "vertex_buffer.h"

namespace undicht {

    namespace graphics {

        SHARED_LIB_DEF_BASE_CLASS(VertexBuffer, createVertexBuffer, copyVertexBuffer, deleteVertexBuffer);

        SHARED_LIB_API_IMPL(VertexBuffer::VertexBuffer()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(VertexBuffer::~VertexBuffer()) {
            //dtor
        }


        SHARED_LIB_API_IMPL(void VertexBuffer::setData(const std::vector<float>& data, unsigned int offset)) {
            m_shared_lib_object->setData(data,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::setData(const void* data, unsigned int size, unsigned int offset)) {
            m_shared_lib_object->setData(data,size,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::setLayout(const core::BufferLayout& layout)) {
            m_shared_lib_object->setLayout(layout);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getData(std::vector<float>& data, unsigned int num_floats, unsigned int offset)) {
            m_shared_lib_object->getData(data,num_floats,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getData(void* data, unsigned int size, unsigned int offset)) {
            /// data should have at least #size bytes reserved
            m_shared_lib_object->getData(data,size,offset);
        }

        SHARED_LIB_API_IMPL(unsigned int VertexBuffer::getSize()) {
            /// returns the number of bytes stored in the buffer
            return m_shared_lib_object->getSize();
        }

        SHARED_LIB_API_IMPL(unsigned int VertexBuffer::getVertexSize()) {
            /// returns the size of one vertex
            return m_shared_lib_object->getVertexSize();
        }

        SHARED_LIB_API_IMPL(const core::BufferLayout& VertexBuffer::getLayout()) {
            /// returns the layout of the stored data
            return m_shared_lib_object->getLayout();
        }


    } // graphics

} // undicht
