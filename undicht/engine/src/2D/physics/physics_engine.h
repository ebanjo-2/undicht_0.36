#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <2D/physics/hitbox.h>
#include <2D/physics/collision.h>
#include <2D/physics/rectangle_hitbox.h>
#include <glm/glm/glm.hpp>

namespace undicht {

    class PhysicsEngine {
        public:

            PhysicsEngine();
            virtual ~PhysicsEngine();

        public:
            // functions to test for collision

            static Collision2D testCollision(const Hitbox2D& hitbox_1, const Hitbox2D& hitbox_2);

            static Collision2D testCollision(const RectangleHitbox& hitbox_1, const RectangleHitbox& hitbox_2);

        public:
            // functions to help with physics calculations

            /** @return a matrix that rotates any 2d vector as if view_dir was the upwards direction (0,1) */
            static glm::mat2 getViewMat(const glm::vec2& view_dir);

            /** the resolution used for collision profiles */
            static float getRes();

        private:
            // functions splitting up collision testing procedures

            /** @return the closest distance between the two hitboxes */
            static float getDistance(const Hitbox2D& hitbox_1, const Hitbox2D& hitbox_2);

            /** @return the time it takes for two objects with speed_1 and speed_2 to collide
            * @param if distance is the distance between their closest points */
            static float calcTimeToCollision(const glm::vec2& speed_1, const glm::vec2& speed_2, const glm::vec2& distance);

    };


} // undicht

#endif // PHYSICS_ENGINE_H
