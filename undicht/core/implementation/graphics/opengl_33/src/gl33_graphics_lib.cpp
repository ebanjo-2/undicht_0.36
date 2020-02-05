#include <glad/glad.h>
#include <graphics/graphics_lib.h>
#include <core/event_logger.h>
#include <functional>

using namespace undicht::core;

namespace undicht {

    namespace graphics {

        namespace implementation {

            void GraphicsLib::initialize(window::GraphicsContext* context) {

                // adding opengl errors to the event classes collection of errors
                Note::setStaticMessage("ERROR 1280: GL_INVALID_ENUM", 1280);
                Note::setStaticMessage("ERROR 1281: GL_INVALID_VALUE", 1281);
                Note::setStaticMessage("ERROR 1282: GL_INVALID_OPERATION", 1282);
                Note::setStaticMessage("ERROR 1283: GL_STACK_OVERFLOW", 1283);
                Note::setStaticMessage("ERROR 1284: GL_STACK_UNDERFLOW", 1284);
                Note::setStaticMessage("ERROR 1285: GL_OUT_OF_MEMORY", 1285);
                Note::setStaticMessage("ERROR 1286: GL_INVALID_FRAMEBUFFER_OPERATION", 1286);


                // initializing glad, hoping that the window lib uses glfw

                if (!gladLoadGLLoader((GLADloadproc)context->getOpenglContextReference())) { //loading all opengl functions
                    EventLogger::storeNote(Note(UND_ERROR,"Failed to initialize GLAD", UND_CODE_ORIGIN ));
                }

                glViewport(0,0,800,600);
                glClearColor(0,1,0,1);
                glClear(GL_COLOR_BUFFER_BIT);


            }

            void GraphicsLib::terminate() {

            }



            SHARED_LIB_EXPORT void initialize(undicht::window::GraphicsContext* context) {

                GraphicsLib::initialize(context);

            }


            SHARED_LIB_EXPORT void terminate() {
                GraphicsLib::terminate();
            }

        } // implementation

    } // graphics

} // undicht

