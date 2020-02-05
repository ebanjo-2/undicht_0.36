#ifndef WALL_H
#define WALL_H

#include <glm/glm/glm.hpp>


namespace undicht {

    class Wall {

        public:

            // for now a wall is a colored line
            glm::vec3 m_pos_0; // the start of the line
            glm::vec3 m_pos_1; // the end of the line

            glm::vec3 m_color;

            Wall();
            Wall(const glm::vec3& pos_0, const glm::vec3& pos_1, const glm::vec3& color);
            virtual ~Wall();

    };


} // undicht

#endif // WALL_H
