#ifndef NOCLIPCAMERA_H
#define NOCLIPCAMERA_H

#include <3D/camera.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>


namespace undicht {



    class NoclipCamera : public Camera3D{
        /// a camera not caring about physics, controlled by wasd keys and the mouse

        public:

            float m_movement_speed = 0.1f;
            float m_mouse_speed = 0.1;

            /** moving based on the user input */
            void update(window::KeyInputWatcher& key_input, window::MouseInputWatcher& mouse_input, window::Window& window);

            NoclipCamera();
            virtual ~NoclipCamera();

    };


} // undicht

#endif // NOCLIPCAMERA_H
