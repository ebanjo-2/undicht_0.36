#include "physics_math.h"



namespace undicht {


    float distance(const glm::vec2& line_base, const glm::vec2& line_dir, const glm::vec2& point) {
        /** @return the distance between the line and a point
        * @param directions should always be normalized */

        glm::vec2 point_to_base = line_base - point;
        glm::vec2 point_to_base_dir = glm::normalize(point_to_base);

        float hypotenuse = glm::length(point_to_base);
        float ankathete = glm::dot(point_to_base_dir, line_dir) * glm::length(point_to_base);
        float gegenkathete = glm::sqrt(glm::pow(hypotenuse, 2.0f) - glm::pow(ankathete, 2.0f));

        return gegenkathete;
    }


    bool intersection(const glm::vec2& start_1, const glm::vec2& end_1, const glm::vec2& start_2, const glm::vec2& end_2, glm::vec2& intersection) {
        /** @return whether the two lines intersect
        * @param intersection: the point of intersection between the two lines */



    }

    std::ostream& operator<< (std::ostream& out, const glm::vec2& vec) {
        out << " " << vec.x << "|" << vec.y;

        return out;
    }


} // undicht
