#ifndef COLLISION_H
#define COLLISION_H

namespace undicht {


    class Collision2D {
        public:
            // details about a collision between two objects

            float m_collision_time = 0;

            /** the calculated time until the collision */
            float getCollisionTime();

            Collision2D();
            virtual ~Collision2D();

    };


} // undicht

#endif // COLLISION_H
