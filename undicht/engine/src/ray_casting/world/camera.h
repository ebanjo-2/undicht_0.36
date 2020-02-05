#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm/glm.hpp>

namespace undicht {


    class Camera {
        public:

            glm::vec3 m_pos;
            float m_yaw = 0; // in degrees
            float m_FoV = 100; // Field of view in degrees

            Camera();
            virtual ~Camera();

    };

} // undicht

#endif // CAMERA_H
