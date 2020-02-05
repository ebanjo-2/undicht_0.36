#ifndef MOVEMENT_PATH_H
#define MOVEMENT_PATH_H

#include <glm/glm/glm.hpp>


namespace undicht {


    class MovementPath2D {
        public:

            glm::vec2 m_start = glm::vec2(0,0);
            glm::vec2 m_velocity = glm::vec2(0,0);


            MovementPath2D();
            virtual ~MovementPath2D();


    };


} // undicht

#endif // MOVEMENT_PATH_H
