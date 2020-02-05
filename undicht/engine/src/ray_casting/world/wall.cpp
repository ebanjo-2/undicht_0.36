#include "wall.h"


namespace undicht {

    Wall::Wall() {

    }


    Wall::Wall(const glm::vec3& pos_0, const glm::vec3& pos_1, const glm::vec3& color) {

        m_pos_0 = pos_0;
        m_pos_1 = pos_1;
        m_color = color;

    }

    Wall::~Wall() {

    }

} // undicht
