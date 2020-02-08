#include "3d_demo.h"
#include <graphics/renderer.h>


namespace undicht {

    using namespace graphics;

    Demo3D::Demo3D(window::Window* window) {

        m_key_input.setWindow(window);
        m_mouse_input.setWindow(window);
        m_window = window;

        m_dae_reader.open("res/models/sponza_collada/sponza.dae");
        m_dae_reader.loadAllSubModels(m_sponza);

        int width, height;
        window->getSize(width, height);

        m_geometry_buffer.setSize(width, height);
        m_geometry_buffer.initialize();

    }

    Demo3D::~Demo3D() {
        //dtor

        m_geometry_buffer.terminate();

    }

    void Demo3D::update() {

        int width, height;
        m_window->getSize(width, height);
        Renderer::setViewport(width, height);
        m_geometry_buffer.setSize(width, height);

        m_key_input.updateChangedKeys();
        m_mouse_input.updateChangedButtons();
        m_mouse_input.updateCursorOffset();

        m_camera.update(m_key_input, m_mouse_input, *m_window);
        m_geometry_buffer.clearAttachments();

    }

    void Demo3D::draw() {

        m_renderer.submit(&m_camera);

        for(TexturedModel& model : m_sponza.m_sub_models) {

            m_renderer.draw(model);

        }

        m_geometry_stage.submit(&m_camera);
        m_geometry_stage.submit(&m_geometry_buffer);

        for(TexturedModel& model : m_sponza.m_sub_models) {

                m_geometry_stage.draw(model);

        }

    }


} // undicht
