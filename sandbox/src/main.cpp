#include <iostream>

#include <core/core.h>
#include <core/event_logger.h>

#include <window/window.h>
#include <window/graphics_context.h>
#include <window/window_lib.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>

#include <graphics/graphics_lib.h>
#include <graphics/vertex_buffer.h>
#include <graphics/shader.h>
#include <graphics/renderer.h>
#include <graphics/uniform.h>
#include <graphics/texture.h>
#include <graphics/frame_buffer.h>

#include <audio/audio_lib.h>
#include <audio/sound_source.h>

#include <file_loading/audio/sound_file_reader.h>
#include <file_loading/file_reader.h>
#include <file_loading/image/image_reader.h>

#include <engine.h>
#include <ray_casting/ray_caster.h>
#include <2D/sprite_renderer.h>

#include <3D/model_renderer.h>
#include <3D/noclip_camera.h>
#include <file_loading/model/collada/collada_file_reader.h>

#include <UI/ui_elements/textured_ui_element.h>
#include <UI/ui_renderer.h>
#include <UI/ui_input_master.h>

#include "ui_demo.h"
#include "3d_demo.h"



using namespace undicht::core;
using namespace undicht::window;
using namespace undicht::graphics;
using namespace undicht::audio;
using namespace undicht;


int main(){

    Window* window;
    GraphicsContext* context;
    Engine::initialize(window, context);

    window->setSize(800, 600);
    window->setTitle("hello world");
    Renderer::setViewport(800, 600);
    // window->setWindowMode(true, false);

    { // engine usage scope



        UIDemo ui_demo(window);
        Demo3D demo_3d(window);


        double first_time = Core::getTime();
        int frame_count = 1;

        // displaying the 3d scene rendered to the geometry buffer on button 1
        ui_demo.m_button.m_texture = demo_3d.m_geometry_buffer.m_albedo;
        ui_demo.m_button_2.m_texture = demo_3d.m_geometry_buffer.m_depth;


        while(!window->shouldClose()) {

            window->update();

            demo_3d.update();
            demo_3d.draw();


            // draw ui on top of 3d
            ui_demo.update();
            ui_demo.draw();




            if(frame_count >= 100) {

                std::cout << "average FPS (last 100 frames): " << frame_count / (Core::getTime() - first_time) << "\n";

                frame_count = 1;
                first_time = Core::getTime();

            }else {
                frame_count++;
            }

            context->swapBuffers();

        }


    } // engine usage scope

    Engine::terminate(window, context);

    return 0;
}
