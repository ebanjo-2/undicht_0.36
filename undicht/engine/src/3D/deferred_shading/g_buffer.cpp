#include "g_buffer.h"
#include <core/types.h>


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

        addAttachment(m_albedo, UND_COLOR_ATTACHMENT);
        addAttachment(m_depth, UND_DEPTH_ATTACHMENT_READ_AND_WRITE);

    }

} // undicht
