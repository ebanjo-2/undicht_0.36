#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <window/window_lib.h>
#include <window/window.h>
#include <functional>


namespace undicht {

    namespace window {

        SHARED_LIB_DECL_BASE_CLASS(GraphicsContext, GraphicsContextBase, createGraphicsContext, copyGraphicsContext, deleteGraphicsContext);

        typedef void(*Proc)();
        typedef Proc (*LoadProcFunc)(const char*);

        SHARED_LIB_CLASS(class GraphicsContext : public GraphicsContextBase {
            /** a class which enables an window to display graphics */
            public:


                GraphicsContext();
                virtual ~GraphicsContext();

                /** the lifetime of the window object should exceed the one of the context */
                virtual void createOnWindow(window::Window* wind);
                virtual void swapBuffers(); // displays the content of the last frame on the window
                virtual void close();

                /** returns the function needed to initialize glad */
                virtual LoadProcFunc  getOpenglContextReference();




        };)




    } //window

} // undicht

#endif // GRAPHICS_CONTEXT_H
