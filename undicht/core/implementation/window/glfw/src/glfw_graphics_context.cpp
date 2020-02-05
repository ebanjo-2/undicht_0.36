#include "glfw_graphics_context.h"
#include <GLFW/glfw3.h>
#include "glfw_window.h"
#include <graphics/renderer.h>


namespace undicht {

    namespace window {

        /*        std::function<implementation::GraphicsContext*()> createContext;
        std::function<void(implementation::GraphicsContext*)> deleteContext;


        namespace implementation {
            GraphicsContext::GraphicsContext(){}
            GraphicsContext::~GraphicsContext(){}
            void GraphicsContext::createOnWindow(window::Window* wind) {}
            void GraphicsContext::clearDefaultFramebuffer() {}
            void GraphicsContext::swapBuffers() {}
            void* GraphicsContext::getOpenglContextReference() {}
        }*/

        graphics::Renderer* renderer = 0; // to clear the viewport

        namespace glfw {


            GraphicsContext::GraphicsContext() {

            }


            GraphicsContext::~GraphicsContext() {

            }

            void GraphicsContext::createOnWindow(window::Window* wind) {
                /** the lifetime of the window object should exceed the one of the context */

                // the glfw window already created a context
                m_window = (glfw::Window*)wind->m_shared_lib_object;

                // cant be done, since the graphics lib was not initialized jet
                // renderer = new graphics::Renderer;
            }


            void GraphicsContext::swapBuffers() {

                glfwSwapBuffers(m_window->m_window);

                if(!renderer)
                    renderer = new graphics::Renderer;

                renderer->clearFramebuffer();
            }

            void GraphicsContext::close(){

                delete renderer;
            }

            LoadProcFunc GraphicsContext::getOpenglContextReference() {

                return glfwGetProcAddress;
            }



            /////////////////////////////////////////// shared lib functions to load GraphicsContext objects /////////////////////////////////////////

            SHARED_LIB_EXPORT undicht::window::implementation::GraphicsContext* createGraphicsContext() {

                return new undicht::window::glfw::GraphicsContext;
            }

            SHARED_LIB_EXPORT void copyGraphicsContext(implementation::GraphicsContext* c, implementation::GraphicsContext* o) {

                *(GraphicsContext*)c = *(GraphicsContext*)o;
            }



            SHARED_LIB_EXPORT void deleteGraphicsContext(undicht::window::implementation::GraphicsContext* context) {

                delete context;
            }


        } // glfw

    } // window

} // undicht


