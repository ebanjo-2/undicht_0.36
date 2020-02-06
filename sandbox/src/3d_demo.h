#ifndef DEMO_3D_H
#define DEMO_3D_H

#include <3D/complex_model.h>
#include <3D/noclip_camera.h>
#include <file_loading/model/collada/collada_file_reader.h>
#include <3D/model_renderer.h>
#include <3D/deferred_shading/geometry_stage_renderer.h>

#include <window/window.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>


namespace undicht {

    class Demo3D {

        public:

            window::KeyInputWatcher m_key_input;
            window::MouseInputWatcher m_mouse_input;
            window::Window* m_window;

        public:

            ComplexTexturedModel m_sponza;
            NoclipCamera m_camera;
            ColladaFileReader m_dae_reader;

            ModelRenderer m_renderer;
            GeometryStageRenderer m_geometry_stage;
            GBuffer m_geometry_buffer;

        public:

            Demo3D(window::Window* window);
            virtual ~Demo3D();

            void update();
            void draw();

    };


} // undicht

#endif // DEMO_3D_H
