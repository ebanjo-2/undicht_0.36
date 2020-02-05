#include <window/window_lib.h>
#include <GLFW/glfw3.h>
#include "glfw_key_ids.h"

namespace undicht {

    namespace window {

        namespace implementation {

            void WindowLib::initialize() {

                glfwInit();
                glfw::setKeyIds();

            }

            void WindowLib::terminate(){

                glfwTerminate();
            }


            SHARED_LIB_EXPORT void initialize() {
                // the only way to export a static function i think
                WindowLib::initialize();

            }

            SHARED_LIB_EXPORT void terminate() {
                WindowLib::terminate();
            }

        }

    }

}
