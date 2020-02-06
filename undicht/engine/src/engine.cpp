#include "engine.h"

#include <core/core.h>
#include <core/string_tools.h>
#include <window/window_lib.h>
#include <graphics/graphics_lib.h>
#include <audio/audio_lib.h>

#include <core/event_logger.h>
#include <iostream>

#include <3D/deferred_shading/geometry_stage_renderer.h>
#include <3D/model_renderer.h>
#include <UI/ui_renderer.h>

namespace undicht {

    using namespace core;
    using namespace graphics;
    using namespace window;
    using namespace audio;

    void Engine::initialize(window::Window* &window, window::GraphicsContext* &context) {



        Core::initialize();


        WindowLib::initialize();
        AudioLib::initialize();

        context = new GraphicsContext;
        window = new Window;
        window->open();
        context->createOnWindow(window);

        GraphicsLib::initialize(context);

        GeometryStageRenderer::initialize();
        ModelRenderer::initialize();
        UIRenderer::initialize();

    }

    void Engine::terminate(window::Window* &window, window::GraphicsContext* &context) {

        UIRenderer::terminate();
        ModelRenderer::terminate();
        GeometryStageRenderer::terminate();

        GraphicsLib::terminate();

        delete context;
        delete window;


        WindowLib::terminate();
        AudioLib::terminate();
        Core::terminate();
    }

    void Engine::coutEventLog() {

        for(const Note& e : EventLogger::getNotes(UND_ERROR)) {
            std::cout << e.getMessage() << "\n";
            std::cout << "  From here: " << e.getOrigin() << "\n";
        }

        for(const Note& e : EventLogger::getNotes(UND_WARNING)) {
            std::cout << e.getMessage() << "\n";
            std::cout << "  From here: " << e.getOrigin() << "\n";
        }

        for(const Note& e : EventLogger::getNotes(UND_MESSAGE)) {
            std::cout << e.getMessage() << "\n";
        }

        EventLogger::clearNotes(UND_ERROR);
        EventLogger::clearNotes(UND_WARNING);
        EventLogger::clearNotes(UND_MESSAGE);

    }

} // undicht
