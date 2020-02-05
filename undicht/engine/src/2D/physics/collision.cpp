#include "collision.h"

namespace undicht {

    Collision2D::Collision2D() {
        //ctor
    }

    Collision2D::~Collision2D() {
        //dtor
    }


    float Collision2D::getCollisionTime() {
        /** the calculated time until the collision */

        return m_collision_time;
    }

} // undicht
