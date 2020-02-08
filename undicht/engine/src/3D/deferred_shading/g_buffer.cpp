#include "g_buffer.h"
#include <core/types.h>
#include <core/buffer_layout.h>


namespace undicht {

    using namespace graphics;
    using namespace core;

    GBuffer::GBuffer() {
        //ctor



    }

    GBuffer::~GBuffer() {
        //dtor
    }


    void GBuffer::initialize() {
        /** to be called after the size was set */

        m_albedo.setPixelFormat(BufferLayout({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR}));
        addAttachment(m_albedo, UND_COLOR_ATTACHMENT);

        // format will be chosen by video lib
        addAttachment(m_depth, UND_DEPTH_ATTACHMENT_READ_AND_WRITE);

    }

    void GBuffer::terminate() {

        // does nothing

    }

} // undicht
