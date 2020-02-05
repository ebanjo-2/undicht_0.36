#include "physics_engine.h"
#include <2D/physics/collision_profile.h>
#include <iostream>
#include <core/string_tools.h>

using namespace undicht::core;

namespace undicht {

    PhysicsEngine::PhysicsEngine() {
        //ctor
    }

    PhysicsEngine::~PhysicsEngine() {
        //dtor
    }

    /////////////////////////////////////// functions to test for collision /////////////////////////////////////

    Collision2D PhysicsEngine::testCollision(const Hitbox2D& hitbox_1, const Hitbox2D& hitbox_2){

        float fdist = getDistance(hitbox_1, hitbox_2);
        glm::vec2 distance = fdist * glm::normalize(hitbox_2.m_position - hitbox_1.m_position);

        Collision2D collision;
        collision.m_collision_time = calcTimeToCollision(hitbox_1.m_speed, hitbox_2.m_speed, distance);


        return collision;
    }

    Collision2D PhysicsEngine::testCollision(const RectangleHitbox& hitbox_1, const RectangleHitbox& hitbox_2) {

        float fdist = RectangleHitbox::getDistance(hitbox_1, hitbox_2);
        glm::vec2 distance = fdist * glm::normalize(hitbox_2.m_position - hitbox_1.m_position);

        Collision2D collision;
        collision.m_collision_time = calcTimeToCollision(hitbox_1.m_speed, hitbox_2.m_speed, distance);


        return collision;
    }

    ////////////////////////////////////// functions to help with physics calculations /////////////////////////////////////////


    glm::mat2 PhysicsEngine::getViewMat(const glm::vec2& view_dir) {
        /** @return a matrix that rotates any 2d vector as if view_dir was the upwards direction (0,1) */

        // creating a view matrix rotating any point as if view_dir pointed up
        glm::vec2 view_tangent = glm::vec2(-view_dir.y, view_dir.x); // rotated 90 degrees


        return glm::mat2 (view_tangent, view_dir);
    }


    float PhysicsEngine::getRes() {
        /** the resolution used for collision profiles */
        return 100;
    }

    //////////////////////////////// functions splitting up collision testing procedures //////////////////////////////////////



    float PhysicsEngine::getDistance(const Hitbox2D& hitbox_1, const Hitbox2D& hitbox_2) {
        /** @return the closest distance between the two hitboxes */

        // calculating the collision profiles for the hitboxes
        glm::vec2 view_point = hitbox_1.m_position + (hitbox_2.m_position - hitbox_1.m_position) * 0.5f;
        glm::vec2 view_dir = glm::normalize(hitbox_2.m_position - hitbox_1.m_position);

        CollisionProfile2D hitbox_1_profile = hitbox_1.getProfile(view_point, view_dir);
        CollisionProfile2D hitbox_2_profile = hitbox_2.getProfile(view_point, view_dir);

        // calculating the distance between the two profiles
        int index_1, index_2; // not used for getting the distance

        return CollisionProfile2D::getClosestPoint(hitbox_1_profile, hitbox_2_profile, false, index_1, index_2);
    }


    float PhysicsEngine::calcTimeToCollision(const glm::vec2& speed_1, const glm::vec2& speed_2, const glm::vec2& distance) {
        /** @return the time it takes for two objects with speed_1 and speed_2 to collide
        * @param if distance is the distance between their closest points */

        /*glm::vec2 norm_distance = glm::normalize(distance);

        float dist_speed_1 = glm::dot(speed_1, norm_distance); // the speed with which the first object is getting closer to the second
        float dist_speed_2 = glm::dot(speed_2, norm_distance);

        return glm::length(distance) / (dist_speed_1 + dist_speed_2);*/
        return glm::length(distance) * 1; // works for now
    }





} // undicht
