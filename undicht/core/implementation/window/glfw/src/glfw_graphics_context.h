#ifndef GLFW_GRAPHICS_CONTEXT_H_INCLUDED
#define GLFW_GRAPHICS_CONTEXT_H_INCLUDED

#include <window/graphics_context.h>
#include <glfw_window.h>


namespace undicht {

    namespace window {

        namespace glfw {


            class GraphicsContext : public implementation::GraphicsContext {
                public:

                    glfw::Window* m_window;

                public:

                    GraphicsContext();
                    virtual ~GraphicsContext();

                    virtual void createOnWindow(window::Window* wind);
                    virtual void swapBuffers();
                    virtual void close();
                    virtual LoadProcFunc getOpenglContextReference();
            };

        } // glfw

    } // window

} // undicht



#endif // GLFW_GRAPHICS_CONTEXT_H_INCLUDED
