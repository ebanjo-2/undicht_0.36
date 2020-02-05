#include "graphics_context.h"
#include <core/core.h>
#include <core/event_logger.h>
#include "window.h"

using namespace undicht::core;

namespace undicht {

    namespace window {


        SHARED_LIB_DEF_BASE_CLASS(GraphicsContext, createGraphicsContext, copyGraphicsContext, deleteGraphicsContext);


        SHARED_LIB_API_IMPL(GraphicsContext::GraphicsContext()) {

        }

        SHARED_LIB_API_IMPL(GraphicsContext::~GraphicsContext()) {

        }


        SHARED_LIB_API_IMPL(void GraphicsContext::createOnWindow(window::Window* wind)) {
            /** the lifetime of the window object should exceed the one of the context */
            m_shared_lib_object->createOnWindow(wind);
        }

        SHARED_LIB_API_IMPL(void GraphicsContext::swapBuffers()) {
            // displays the content of the last frame on the window
            m_shared_lib_object->swapBuffers();
        }

        SHARED_LIB_API_IMPL(void GraphicsContext::close()) {

            m_shared_lib_object->close();
        }

        SHARED_LIB_API_IMPL(LoadProcFunc GraphicsContext::getOpenglContextReference()) {
            return m_shared_lib_object->getOpenglContextReference();
        }

    } // window

} // undicht
