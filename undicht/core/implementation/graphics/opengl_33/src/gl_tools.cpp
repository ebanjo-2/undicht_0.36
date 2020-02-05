#include <glad/glad.h>
#include "gl_tools.h"
#include <core/event_logger.h>

using namespace undicht::core;


namespace undicht {

    namespace graphics {

        namespace gl33 {

            void undCheckGLError(const std::string& origin) {
                unsigned int gl_error = glGetError();

                if(gl_error)
                    EventLogger::storeNote(Note(UND_ERROR, gl_error, origin));

            }

        } //gl33

    } // graphics

} // undicht
