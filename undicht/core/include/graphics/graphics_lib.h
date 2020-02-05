#ifndef GRAPHICS_LIB_H
#define GRAPHICS_LIB_H

#include <core/shared_lib.h>
#include <window/graphics_context.h>

namespace undicht {

    namespace graphics {


        SHARED_LIB_CLASS(class GraphicsLib {
            public:

                static void initialize(window::GraphicsContext* context);

                static void terminate();

                GraphicsLib();
                virtual ~GraphicsLib();


        };)

    } // graphics

} // undicht


#endif // GRAPHICS_LIB_H
