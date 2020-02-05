#include "window_lib.h"
#include "window/window.h"
#include "window/graphics_context.h"
#include <core/core.h>
#include "window/key_input_watcher.h"
#include "window/mouse_input_watcher.h"

namespace undicht {

    namespace window {

        SHARED_LIB_API_IMPL(WindowLib::WindowLib()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(WindowLib::~WindowLib()) {
            //dtor
        }

        // this function should also be implemented in the shared window lib
        // it can be used to initialize further, implementation specific libraries
        // there also needs to be a global, non static function that calls the WindowLib::initialize function called initialize()
        void WindowLib::initialize() {


            ((void(*)())core::Core::s_window_lib.getFunction("initialize")) ();

            createWindow = (implementation::Window*(*)())core::Core::s_window_lib.getFunction("createWindow");
            copyWindow = (void(*)(implementation::Window*,implementation::Window*))core::Core::s_window_lib.getFunction("copyWindow");
            deleteWindow = (void(*)(implementation::Window*))core::Core::s_window_lib.getFunction("deleteWindow");

            createGraphicsContext = (implementation::GraphicsContext*(*)())core::Core::s_window_lib.getFunction("createGraphicsContext");
            copyGraphicsContext = (void(*)(implementation::GraphicsContext*,implementation::GraphicsContext*))core::Core::s_window_lib.getFunction("copyGraphicsContext");
            deleteGraphicsContext = (void(*)(implementation::GraphicsContext*))core::Core::s_window_lib.getFunction("deleteGraphicsContext");

            createKeyInputWatcher = (implementation::KeyInputWatcher*(*)())core::Core::s_window_lib.getFunction("createKeyInputWatcher");
            copyKeyInputWatcher = (void(*)(implementation::KeyInputWatcher*,implementation::KeyInputWatcher*))core::Core::s_window_lib.getFunction("copyKeyInputWatcher");
            deleteKeyInputWatcher = (void(*)(implementation::KeyInputWatcher*))core::Core::s_window_lib.getFunction("deleteKeyInputWatcher");

            createMouseInputWatcher = (implementation::MouseInputWatcher*(*)())core::Core::s_window_lib.getFunction("createMouseInputWatcher");
            copyMouseInputWatcher = (void(*)(implementation::MouseInputWatcher*,implementation::MouseInputWatcher*))core::Core::s_window_lib.getFunction("copyMouseInputWatcher");
            deleteMouseInputWatcher = (void(*)(implementation::MouseInputWatcher*))core::Core::s_window_lib.getFunction("deleteMouseInputWatcher");
        }

        void WindowLib::terminate(){

              ((void(*)())core::Core::s_window_lib.getFunction("terminate")) ();

        }


    } // window

} // undicht
