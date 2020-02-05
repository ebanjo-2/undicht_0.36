#include <GLFW/glfw3.h>
// the glfw implementation of the Window class

#include "glfw_window.h"
#include <core/event_logger.h>
#include <iostream>
#include <core/shared_lib.h>
#include <core/string_tools.h>

using namespace undicht::core;

namespace undicht {

    namespace window {

        namespace glfw {

            Window::Window() {

            }

            Window::~Window() {
                // doing nothing
            }


            void Window::open() {
                /** open the window */

                m_window = glfwCreateWindow(m_width, m_height, m_title.data(), NULL, NULL); //glfwGetPrimaryMonitor() for fullscreen

                if (m_window == NULL) {
                    EventLogger::storeNote(Note(UND_ERROR, "WINDOW:ERROR: Failed to create GLFW window", UND_CODE_ORIGIN));
                    return;
                }

                glfwMakeContextCurrent(m_window);

            }

            void Window::open(int width, int height, const std::string& title) {
                setSize(width, height);
                setTitle(title);
                open();
            }

            void Window::close() {
                // to be done
            }

            void Window::update() {
                getSize(m_width, m_height);
                glfwPollEvents();
            }

            bool Window::shouldClose() {
                /** \return whether a close was requested by the user */

                return glfwWindowShouldClose(m_window);
            }


            void Window::setSize(int width, int height) {

                m_width = width;
                m_height = height;

                if(m_window) {
                    glfwSetWindowSize(m_window, width, height);
                } // to be done

            }

            void Window::getSize(int& width, int& height) {

                glfwGetWindowSize(m_window, &width, &height);

            }

            void Window::setTitle(const std::string& title) {

                m_title = title;

                if(m_window) {
                    glfwSetWindowTitle(m_window, title.data());
                }

            }

            void Window::setWindowMode(bool fullscreen, bool windowed) {
                // still to be done
                if(windowed){
                    m_window = glfwCreateWindow(m_width, m_height, m_title.data(), NULL, NULL);
                } else {
                    m_window = glfwCreateWindow(m_width, m_height, m_title.data(), glfwGetPrimaryMonitor(), NULL);
                }
            }

            void Window::setCursorVisible(bool visible) {

                m_cursor_visible = visible;

                if(visible) {
                    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                } else {
                    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//cursor disappears
                }

            }

            bool Window::getCursorVisible() {

                return m_cursor_visible;
            }



            /////////////////////////////////////////// shared lib functions to load Window objects /////////////////////////////////////////

            SHARED_LIB_EXPORT implementation::Window* createWindow() {

                return new glfw::Window;
            }


            SHARED_LIB_EXPORT void copyWindow(implementation::Window* c, implementation::Window* o) {

                *(Window*)c = *(Window*)o;
            }


            SHARED_LIB_EXPORT void deleteWindow(implementation::Window* window) {

                delete /*(undicht::window::glfw::Window*)*/window;
            }



        } // glfw


    } // window

} // undicht


