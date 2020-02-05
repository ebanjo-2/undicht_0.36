#include "collision_profile.h"
#include <core/event_logger.h>
#include <glm/glm/glm.hpp>
#include <2D/physics/physics_engine.h>

using namespace undicht::core;

namespace undicht {

    CollisionProfile2D::CollisionProfile2D() {
        //ctor
    }

    CollisionProfile2D::~CollisionProfile2D() {
        //dtor
    }

    void CollisionProfile2D::setWidth(int width, float initial_depth) {

        m_depth.resize(width);


        for(float& f : m_depth) {
            f = initial_depth;
        }

    }

    void CollisionProfile2D::setDepth(int index, float depth, bool overwrite) {


        float& d = m_depth.at(index);

        if(overwrite) {

            d = depth;

        } else {

            if(d > depth) {
                d = depth;
            }
        }

    }

    void CollisionProfile2D::addInterpolatedLine(int index_1, float depth_1, int index_2, float depth_2) {
        /** adds the points to the profile and adds the interpolated depth values
        * the depth values are only written if their depth value is closer to 0 then the ones being replaced */

        if((index_1 >= m_depth.size()) || (index_2 >= m_depth.size()) || (index_1 < 0) || (index_2 < 0)) {
            EventLogger::storeNote(Note(UND_ERROR, "PHYSICS:2D:ERROR: line of depth values cant be set, invalid index (1) " + toStr(index_1) + " (2) " + toStr(index_2) + " max index: " + toStr(int(m_depth.size()) - 1) , UND_CODE_ORIGIN));
            return;
        }


        bool reverse_indices = index_1 < index_2;

        int start = reverse_indices ? index_1 : index_2;
        int stop = reverse_indices ? index_2 : index_1;

        int steps = stop - start;

        if(!steps){
            setDepth(start,depth_1 > depth_2 ? depth_1 : depth_2);
            return;
        }

        for(int i = 0; i < steps; i++) {
            if(reverse_indices) {
                setDepth(i + start, depth_2 + (depth_1 - depth_2) * i / steps);
            } else {
                setDepth(i + start, depth_1 + (depth_2 - depth_1) * i / steps);
            }
        }


    }


    float CollisionProfile2D::getClosestPoint(const CollisionProfile2D& p1, const CollisionProfile2D& p2, bool reverse_p2, int& p1_index, int& p2_index) {
        /** @return the smallest difference between the profile p1 and p2
        @param reverse_profile: whether to multiply the depth of the second profile with -1 before subtracting them from the p1 profile
        @param index: the index of the depth value closest to the other profile */

        // a short to reverse the depth values of p2 with
        short rev = 1;
        if(reverse_p2) {
            rev = -1;
        }

        // searching for the indices to start on, so that the compared depth values of p1 and p2 allign
        float p1_start = p1.m_offset - p1.m_mid / PhysicsEngine::getRes();
        float p2_start = p2.m_offset - p2.m_mid / PhysicsEngine::getRes();

        int p1_iterator = 0;
        int p2_iterator = 0;

        if(p1_start > p2_start) {
            p2_iterator = (p1_start - p2_start) * PhysicsEngine::getRes();
        } else if ( p1_start < p2_start){
            p1_iterator = (p2_start - p1_start) * PhysicsEngine::getRes();
        } // else: do nothing

        float closest_distance = 1000.0f; // some big number


        // checking for the smallest distance
        while((p1_iterator < p1.m_depth.size()) && (p2_iterator < p2.m_depth.size())) {

            float dist = rev * p2.m_depth.at(p2_iterator) - p1.m_depth.at(p1_iterator);
            //std::cout << "depths 1: " << p1.m_depth.at(p1_iterator) << "\n";
            //std::cout << "depths 2: " << p2.m_depth.at(p2_iterator) << "\n";

            if(closest_distance > dist) {
                closest_distance = dist;
                p1_index = p1_iterator;
                p2_index = p2_iterator;
            }

            p1_iterator += 1;
            p2_iterator += 1;

        }

        return closest_distance;
    }

    ////////////////////////////////////// functions to help creating collision profiles /////////////////////////////////////

    glm::vec2 CollisionProfile2D::pointToProfile(const glm::vec2& point, const glm::vec2& view_pos, const glm::mat2& view_mat) {
        /** @return the point transformed into the profile view seen from the view_pos */

        return view_mat * (point - view_pos);
    }


    int CollisionProfile2D::smallestX(glm::vec2* vecs, int num) {
        /** @return the index of the vector with the smallest x component */

        if(num <= 0) return -1;

        int index = 0;
        int smallest = vecs[0].x;

        for(int i = 0; i < num; i++){
            if(vecs[i].x < smallest){
                smallest = vecs[i].x;
                index = i;
            }
        }

        return index;
    }


    int CollisionProfile2D::biggestX(glm::vec2* vecs, int num) {
        /** @return the index of the vector with the biggest x component */
        if(num <= 0) return -1;

        int index = 0;
        int biggest = vecs[0].x;

        for(int i = 0; i < num; i++){
            if(vecs[i].x > biggest){
                biggest = vecs[i].x;
                index = i;
            }
        }

        return index;
    }


    int CollisionProfile2D::toProfileIndex(float coordinate) {

        return coordinate * PhysicsEngine::getRes();
    }

    float CollisionProfile2D::toCoordinate(int profile_index) {

        return profile_index / PhysicsEngine::getRes();
    }




} // undicht
