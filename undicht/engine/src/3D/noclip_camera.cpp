#include "noclip_camera.h"


namespace undicht {

    using namespace window;

    NoclipCamera::NoclipCamera() {
        //ctor
    }

    NoclipCamera::~NoclipCamera() {
        //dtor
    }


    void NoclipCamera::update(window::KeyInputWatcher& key_input, window::MouseInputWatcher& mouse_input, window::Window& window) {

        if(key_input.getKeyState(UND_KEY_LSHIFT)) {
            m_movement_speed = 1;
        } else {
            m_movement_speed = 0.1;
        }

        if(key_input.getKeyState(UND_KEY_W)) {
            setPosition(m_position + m_movement_speed * getViewDir(), false);
        }

        if(key_input.getKeyState(UND_KEY_S)) {
            setPosition(m_position - m_movement_speed * getViewDir(), false);
        }

        if(key_input.getKeyState(UND_KEY_D)) {
            setPosition(m_position + m_movement_speed * (glm::cross(getViewDir(), glm::vec3(0.0f,1.0f,0.0f))), false);
        }

        if(key_input.getKeyState(UND_KEY_A)) {
            setPosition(m_position - m_movement_speed * (glm::cross(getViewDir(), glm::vec3(0.0f,1.0f,0.0f))), false);
        }

        if(key_input.getKeyState(UND_KEY_Q)) {
            window.setCursorVisible(!window.getCursorVisible());
        }

        int offset_x, offset_y;
        mouse_input.getCursorOffset(offset_x, offset_y);

        float pitch = m_pitch + offset_y * m_mouse_speed;
        float yaw = m_yaw + offset_x * m_mouse_speed;

        setRotation(pitch, yaw, 0, false);

        updateView();

    }

} // undicht
