#include "3d_demo.h"


namespace undicht {


    Demo3D::Demo3D(window::Window* window) {

        m_key_input.setWindow(window);
        m_mouse_input.setWindow(window);
        m_window = window;

        m_dae_reader.open("res/models/sponza_collada/sponza.dae");
        m_dae_reader.loadAllSubModels(m_sponza);

    }

    Demo3D::~Demo3D() {
        //dtor
    }

    void Demo3D::update() {

        m_key_input.updateChangedKeys();
        m_mouse_input.updateChangedButtons();
        m_mouse_input.updateCursorOffset();

        m_camera.update(m_key_input, m_mouse_input, *m_window);

    }

    void Demo3D::draw() {

        m_renderer.submit(&m_camera);

        for(TexturedModel& model : m_sponza.m_sub_models) {

                m_renderer.draw(model);

        }

    }


} // undicht
