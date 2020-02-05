#ifndef RECTANGLE_HITBOX_H
#define RECTANGLE_HITBOX_H


#include <glm/glm/glm.hpp>
#include <2D/physics/hitbox.h>
#include <array>

namespace undicht {


    class RectangleHitbox : public Hitbox2D {

        public:

            glm::vec2 m_size; // width and height

        public:

            RectangleHitbox();
            virtual ~RectangleHitbox();

        public:
            // functions to test for collisions with known shapes

            /** @return the closest distance between the hitboxes */
            static float getDistance(const RectangleHitbox& h1, const RectangleHitbox& h2);

            /** @return a point on the surface of the rectangle relative to m_position
            * on the line in the direction of dir starting at m_position */
            glm::vec2 getSurfacePoint(const glm::vec2& dir) const;

        public:
            // functions to test for collisions with collision profiles (very inefficient, other methods should be preferred, but should work with almost any shape)

            /** @return the profile as seen from the view_point in the direction of the view_normal
            * the projection of the 2D shape is orthographic */
            virtual CollisionProfile2D getProfile(const glm::vec2& view_point, const glm::vec2& view_normal) const;

            /** @return the vertices of the rectangle */
            std::array<glm::vec2,4> getVertices() const;

            /** @return the vertices transformed into the view of the profile */
            std::array<glm::vec2,4> getProfileVertices(const std::array<glm::vec2,4>& vertices, const glm::vec2& view_pos, const glm::mat2& view_mat) const;

            void storeInProfile(const std::array<glm::vec2,4>& profile_vertices, CollisionProfile2D& profile) const;

    };


} // undicht

#endif // RECTANGLE_HITBOX_H
