#ifndef GL_TOOLS_H_INCLUDED
#define GL_TOOLS_H_INCLUDED


#include <core/event_logger.h>


#define UND_CHECK_GL_ERROR()



namespace undicht {

    namespace graphics {

        namespace gl33 {

            void undCheckGLError(const std::string& origin);

        } //gl33

    } // graphics

} // undicht



#endif // GL_TOOLS_H_INCLUDED
