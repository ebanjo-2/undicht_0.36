#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "world/wall.h"
#include "world/camera.h"
#include <glm/glm/glm.hpp>


// this is my first attempt at creating a doom / wolfenstein like 3d renderer


namespace undicht {

    class RayCaster {
        public:

            Camera m_cam;

            void draw(const Wall& wall);

            void submit(const Camera& cam);

            RayCaster();
            virtual ~RayCaster();

        private:

            void drawLine(glm::vec2 pos_0, glm::vec2 pos_1);
            void toScreenCoords(const glm::vec3& world_pos, glm::vec2& result);;

    };

} // undicht

#endif // RAYCASTER_H
