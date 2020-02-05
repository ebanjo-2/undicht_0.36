#include "object.h"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>

#include <glm/glm/gtc/type_ptr.hpp>

#include <core/types.h>

using namespace undicht::core;

namespace undicht {

    Object3D::Object3D() {
        //ctor

        setScale(m_scale);
        updateTransfMat();

    }

    Object3D::~Object3D() {
        //dtor
    }

    void Object3D::setPosition(const glm::vec3& position, bool update_transf) {

        m_position = position;

        if(update_transf)
            updateTransfMat();
    }


    const glm::vec3& Object3D::getPosition() const {

        return m_position;
    }

    void Object3D::setScale(const glm::vec3& scale) {

        m_scale = scale;
        m_scale_uniform.setData(glm::value_ptr(scale), UND_VEC3F, true);
    }


    const glm::vec3& Object3D::getScale() {

        return m_scale;
    }


    void Object3D::setRotation(float pitch, float yaw, float roll, bool update_transf) {
        /// sets the rotation relative to the objects center

        m_pitch = pitch;
        m_yaw = yaw;
        m_roll = roll;

        if(update_transf)
            updateTransfMat();

    }

    void Object3D::getRotation(float& pitch, float& yaw, float& roll) const {

        pitch = m_pitch;
        yaw = m_yaw;
        roll = m_roll;

    }


    const glm::mat4& Object3D::getTransfMat() {

        return m_transf_mat;
    }

    void Object3D::updateTransfMat() {

        // i think this would have worked in an older version of glm
        /*glm::quat rotation = glm::angleAxis(glm::radians(m_roll), glm::vec3(0,0,1));
        rotation *= glm::angleAxis(glm::radians(m_pitch), glm::vec3(1,0,0));
        rotation *= glm::angleAxis(glm::radians(m_yaw), glm::vec3(0,1,0));*/

        // this is what im going to try now, since i have no idea how quaternions work
        glm::quat rotation = glm::angleAxis(glm::radians(m_roll), glm::vec3(0,0,1));
        rotation = glm::cross(rotation, glm::angleAxis(glm::radians(m_pitch), glm::vec3(1,0,0)));
        rotation = glm::cross(rotation, glm::angleAxis(glm::radians(m_yaw), glm::vec3(0,1,0)));

        m_transf_mat = glm::toMat4(rotation) * glm::translate(glm::mat4(1.0f), m_position) ;
        m_transf_uniform.setData(glm::value_ptr(m_transf_mat), UND_MAT4F, true);

    }

} // undicht
