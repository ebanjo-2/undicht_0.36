#include <graphics/frame_buffer.h>


namespace undicht {

    namespace graphics {

        SHARED_LIB_DEF_BASE_CLASS( FrameBuffer, createFrameBuffer, copyFrameBuffer, deleteFrameBuffer);

        SHARED_LIB_API_IMPL(FrameBuffer::FrameBuffer()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(FrameBuffer::~FrameBuffer()) {
            //dtor
        }


        SHARED_LIB_API_IMPL(void FrameBuffer::setSize(int width, int height)) {
            /** setting the size of the framebuffer and all of its attachments */

            m_shared_lib_object->setSize(width, height);
        }

        SHARED_LIB_API_IMPL(void FrameBuffer::getSize(int& width, int& height)) {

            m_shared_lib_object->getSize(width, height);
        }


        SHARED_LIB_API_IMPL(void FrameBuffer::addAttachment(graphics::Texture& texture, int attachment_type)) {
            /** @param texture: the framebuffer can only be used while the texture object exists
            * @param attachment_type: UND_COLOR_ATTACHMENT, UND_DEPTH_ATTACHMENT_WRITE_ONLY or UND_DEPTH_ATTACHMENT_READ_AND_WRITE */

            m_shared_lib_object->addAttachment(texture, attachment_type);
        }


        SHARED_LIB_API_IMPL(void FrameBuffer::removeAttachment(graphics::Texture& texture)) {
            /** @brief removes the attachment from the framebuffer */

            m_shared_lib_object->removeAttachment(texture);
        }

        SHARED_LIB_API_IMPL(void FrameBuffer::clearAttachments()) {
            /** @brief removes the attachment from the framebuffer */

            m_shared_lib_object->clearAttachments();
        }


    } // graphics

} // undicht
