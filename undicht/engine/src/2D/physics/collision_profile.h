#ifndef COLLISION_PROFILE_H
#define COLLISION_PROFILE_H

#include <vector>
#include <glm/glm/glm.hpp>


namespace undicht {

    class CollisionProfile2D {
            /** a collision profile is the side view of a hitbox (1d line in the case of 2d shapes)
            * with depth values for segments of the line, much like a 1d depth texture
            * it can be used to calculate the point at which two objects collide */
        public:

            int m_mid = 0; // index into m_depth, for a depth value behind which the position point of the shape is

            float m_offset = 0; // the distance between the mid of the shape and the mid of the view used to calculate the profile
            float m_width = 0; // the (screen coordinate) width of the line with the depth values
            std::vector<float> m_depth; // the depth values

            void setWidth(int width, float initial_depth = 0.0f);

            void setDepth(int index, float depth, bool overwrite = false);

            /** adds the points to the profile and adds the interpolated depth values
            * the depth values are only written if their depth value is closer to 0 then the ones being replaced */
            void addInterpolatedLine(int index_1, float depth_1, int index_2, float depth_2);

            /** @return the smallest difference between the profile p1 and p2
            @param reverse_profile: whether to multiply the depth of the second profile with -1 before subtracting them from the p1 profile
            @param index: the index of the depth value closest to the other profile */
            static float getClosestPoint(const CollisionProfile2D& p1, const CollisionProfile2D& p2, bool reverse_p2, int& p1_index, int& p2_index);

        public:
            // functions to help creating collision profiles

            /** @return the point transformed into the profile view seen from the view_pos */
            static glm::vec2 pointToProfile(const glm::vec2& point, const glm::vec2& view_pos, const glm::mat2& view_mat);

            /** @return the index of the vector with the smallest x component */
            static int smallestX(glm::vec2* vecs, int num);

            /** @return the index of the vector with the biggest x component */
            static int biggestX(glm::vec2* vecs, int num);

            static int toProfileIndex(float coordinate);

            static float toCoordinate(int profile_index);

            CollisionProfile2D();
            virtual ~CollisionProfile2D();

    };


} // undicht

#endif // COLLISION_PROFILE_H
