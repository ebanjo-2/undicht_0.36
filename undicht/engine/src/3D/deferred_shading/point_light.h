#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm/glm.hpp>


namespace undicht {


    class PointLight {
        public:

            glm::vec3 m_position;
            glm::vec3 m_color;

            PointLight();
            virtual ~PointLight();

    };

} // undicht

#endif // POINT_LIGHT_H
