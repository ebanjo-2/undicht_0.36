#ifndef PHYSICS_MATH_H
#define PHYSICS_MATH_H

#include <glm/glm/glm.hpp>
#include <iostream>


namespace undicht {


    /** @return the distance between the line and a point
    * @param directions should always be normalized */
    float distance(const glm::vec2& line_base, const glm::vec2& line_dir, const glm::vec2& point);

    /** @return whether the two lines intersect
    * @param intersection: the point of intersection between the two lines */
    bool intersection(const glm::vec2& start_1, const glm::vec2& end_1, const glm::vec2& start_2, const glm::vec2& end_2, glm::vec2& intersection);

    std::ostream& operator<< (std::ostream& out, const glm::vec2& vec);


} // undicht


#endif // PHYSICS_MATH_H
