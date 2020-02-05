#include <window/window.h>
#include <core/core.h>
#include <core/event_logger.h>

using namespace undicht::core;

namespace undicht {

    namespace window {

        SHARED_LIB_DEF_BASE_CLASS(Window, createWindow, copyWindow, deleteWindow);


        SHARED_LIB_API_IMPL(Window::Window()) {

        }


        SHARED_LIB_API_IMPL(Window::~Window()) {

        }


        /** opens the window */
        SHARED_LIB_API_IMPL(void Window::open()) {

            m_shared_lib_object->open();
        }

        SHARED_LIB_API_IMPL(void Window::open(int width, int height, const std::string& title)) {

            m_shared_lib_object->open(width, height, title);
        }

        SHARED_LIB_API_IMPL(void Window::close()) {

            m_shared_lib_object->close();
        }

        SHARED_LIB_API_IMPL(void Window::update()) {

            m_shared_lib_object->update();
        }

        /** \return whether a close was requested by the user */
        SHARED_LIB_API_IMPL(bool Window::shouldClose()) {

            return m_shared_lib_object->shouldClose();
        }

        SHARED_LIB_API_IMPL(void Window::setSize(int width, int height)) {

            m_shared_lib_object->setSize(width, height);
        }

        SHARED_LIB_API_IMPL(void Window::getSize(int& width, int& height)) {

            m_shared_lib_object->getSize(width, height);
        }

        SHARED_LIB_API_IMPL(void Window::setTitle(const std::string& title)) {

            m_shared_lib_object->setTitle(title);
        }

        SHARED_LIB_API_IMPL(void Window::setWindowMode(bool fullscreen, bool windowed)) {

            m_shared_lib_object->setWindowMode(fullscreen, windowed);
        }

        SHARED_LIB_API_IMPL(void Window::setCursorVisible(bool visible)) {

            m_shared_lib_object->setCursorVisible(visible);
        }

        SHARED_LIB_API_IMPL(bool Window::getCursorVisible()) {

            return m_shared_lib_object->getCursorVisible();
        }



    } // window

} // undicht
