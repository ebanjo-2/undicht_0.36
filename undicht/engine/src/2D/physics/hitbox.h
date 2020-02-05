#ifndef HITBOX2D_H
#define HITBOX2D_H

#include <glm/glm/glm.hpp>
#include <2D/physics/collision.h>
#include <2D/physics/collision_profile.h>


namespace undicht {


    class Hitbox2D {
        public:
            // screen coordinates [-1 - 1] are on the screen
            glm::vec2 m_position;
            glm::vec2 m_speed; // movement per second

            /** @return the profile as seen from the view_point in the direction of the view_normal
            * the projection of the 2D shape is orthographic
            * @param view_normal should be normalized
            * @return depth values will be negative if the shape is "behind" the view point */
            virtual CollisionProfile2D getProfile(const glm::vec2& view_point, const glm::vec2& view_normal) const;


            Hitbox2D();
            virtual ~Hitbox2D();

    };

} // undicht

#endif // HITBOX2D_H
