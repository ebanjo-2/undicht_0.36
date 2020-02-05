#ifndef WINDOW_LIB_H
#define WINDOW_LIB_H

#include <core/shared_lib.h>
#include <core/shared_lib_class.h>
#include <functional>

#include <core/shared_lib_class.h>


namespace undicht {

    namespace window {


        SHARED_LIB_CLASS( class WindowLib {
                /** the class that manages the window library
                * i.e. loading the functions to load objects from the library */
            public:

                static void initialize();

                static void terminate();

                WindowLib();
                virtual ~WindowLib();


        };)

    } // window

} // undicht

#endif // WINDOW_LIB_H
