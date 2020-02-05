#ifndef ENGINE_H
#define ENGINE_H

#include <window/graphics_context.h>


namespace undicht {


    class Engine {
        /** a class that should make using the undicht engine easier */
        public:

            /** initializes the engine,
            * @param stores engines main window and graphics context
            * @warning !!!! any further usage of engine objects/functions should be made in a block that runs out before terminate is called !!!! */
            static void initialize(window::Window* &window, window::GraphicsContext* &context);

            /** terminates the engine */
            static void terminate(window::Window* &window, window::GraphicsContext* &context);

            /** prints the event log to the console*/
            static void coutEventLog();
    };


} // undicht

#endif // ENGINE_H
