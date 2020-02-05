#include "rectangle_hitbox.h"
#include <2D/physics/physics_engine.h>
#include <iostream>
#include <2D/physics/physics_math.h>


namespace undicht {



    RectangleHitbox::RectangleHitbox() {
        //ctor
    }

    RectangleHitbox::~RectangleHitbox() {
        //dtor
    }

    ////////////////////////////////////// functions to test for collisions with known shapes /////////////////////////////

    float RectangleHitbox::getDistance(const RectangleHitbox& h1, const RectangleHitbox& h2) {
        /** @return the closest distance between the hitboxes */

        // calculating without rotation should be easy
        // but this should do for the breakout game

        glm::vec2 distance = h2.m_position - h1.m_position;
        glm::vec2 dir = glm::normalize(distance);


        return glm::length(distance) - glm::length(h1.getSurfacePoint(dir)) - glm::length(h2.getSurfacePoint(dir));
    }



    glm::vec2 RectangleHitbox::getSurfacePoint(const glm::vec2& norm_dir) const{

        glm::vec2 point;

        // testing whether its a point on a side
        if((norm_dir.y == 0) || (m_size.y == 0) || (glm::length(norm_dir.x / norm_dir.y) > glm::length(m_size.x / m_size.y))) {
            // point on the side

            point.x = norm_dir.x > 0 ? m_size.x : -1 * m_size.x;
            point.y = norm_dir.y / norm_dir.x * m_size.x;

        } else {
            // top or bottom

            point.x = norm_dir.x / norm_dir.y * m_size.y;
            point.y = norm_dir.y > 0 ? m_size.y : -1 * m_size.y;
        }

        return point;
    }





    ////////////////////////////////////////////////////// collision profile ////////////////////////////////////////////

    CollisionProfile2D RectangleHitbox::getProfile(const glm::vec2& view_point, const glm::vec2& view_normal) const {


        CollisionProfile2D rectangle_profile;

        // creating a view matrix rotating any point as if view_normal pointed up
        glm::mat2 view_mat = PhysicsEngine::getViewMat(view_normal);

        // transforming the vertices of the rectangle
        std::array<glm::vec2,4> vertices = getVertices();
        std::array<glm::vec2,4> profile_vertices = getProfileVertices(vertices, view_point, view_mat);


        // finding the width of the transformed rectangle seen from the view_point (transformed to 0|0 )
        float most_left = profile_vertices[CollisionProfile2D::smallestX(profile_vertices.data(), 4)].x;
        float most_right = profile_vertices[CollisionProfile2D::biggestX(profile_vertices.data(), 4)].x;
        float view_width = most_right - most_left;


        // calculating the number of depth values in the profile
        int pixel_count = CollisionProfile2D::toProfileIndex(view_width);
        rectangle_profile.setWidth(pixel_count, 1000.0f);

        // calculating the index of each point in the profile
        int index_offset = CollisionProfile2D::toProfileIndex(most_left);

        for(glm::vec2& v : profile_vertices) {
            v.x = CollisionProfile2D::toProfileIndex(v.x) - index_offset;
        }

        // calculating the index of the mid
        rectangle_profile.m_mid = pixel_count / 2;

        // storing the 4 edges in the profile
        storeInProfile(profile_vertices, rectangle_profile);

        // finding the distance between the view mid and m_position
        rectangle_profile.m_offset = CollisionProfile2D::pointToProfile(m_position, view_point, view_mat).x;


        return rectangle_profile;
    }


    std::array<glm::vec2,4> RectangleHitbox::getVertices() const{
        /** @return the vertices of the rectangle */

        return std::array<glm::vec2, 4>{
                glm::vec2(m_size * glm::vec2( 1, 1)), // top right
                glm::vec2(m_size * glm::vec2( 1,-1)), // bottom right
                glm::vec2(m_size * glm::vec2(-1,-1)), // bottom left
                glm::vec2(m_size * glm::vec2(-1, 1))  // top left
        };
    }


    std::array<glm::vec2,4> RectangleHitbox::getProfileVertices(const std::array<glm::vec2,4>& vertices, const glm::vec2& view_pos, const glm::mat2& view_mat) const{
        /** @return the vertices transformed into the view of the profile */

        std::array<glm::vec2, 4> transformed_vertices;

        for(int i = 0; i < 4; i++) {
            transformed_vertices[i] = CollisionProfile2D::pointToProfile(m_position + vertices[i], view_pos, view_mat);
        }

        return transformed_vertices;
    }

    void RectangleHitbox::storeInProfile(const std::array<glm::vec2,4>& profile_vertices, CollisionProfile2D& profile) const {

        profile.addInterpolatedLine(profile_vertices[0].x, profile_vertices[0].y, profile_vertices[1].x, profile_vertices[1].y);
        profile.addInterpolatedLine(profile_vertices[1].x, profile_vertices[1].y, profile_vertices[2].x, profile_vertices[2].y);
        profile.addInterpolatedLine(profile_vertices[2].x, profile_vertices[2].y, profile_vertices[3].x, profile_vertices[3].y);
        profile.addInterpolatedLine(profile_vertices[3].x, profile_vertices[3].y, profile_vertices[0].x, profile_vertices[0].y);

    }

} // undicht
