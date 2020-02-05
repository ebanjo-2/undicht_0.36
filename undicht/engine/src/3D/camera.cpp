#include <3D/camera.h>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <core/types.h>


namespace undicht {

    using namespace core;

    Camera3D::Camera3D() {
        //ctor

        updateProj();
        updateView();

        m_view_uniform.setName("view");
        m_proj_uniform.setName("projection");

    }

    Camera3D::~Camera3D() {
        //dtor
    }


    void Camera3D::setProjectionMode(bool perspective) {
        /** whether to create the illusion of perspective
        * (making objects further away appear smaller) */

        m_use_perspective = perspective;
        updateProj();

    }

    bool Camera3D::getProjectionMode() const {

        return m_use_perspective;
    }


    void Camera3D::setFoV(float fov) {
        /** if the Camera3D is orthographic, this sets the width of the view */

        m_FoV = fov;
        updateProj();

    }

    float Camera3D::getFoV() const {

        return m_FoV;
    }


    void Camera3D::setAspectRatio(float aspect_ratio) {
        /** the ratio between the width and the height of the field of view  */

        m_aspect_ratio = aspect_ratio;
        updateProj();

    }

    float Camera3D::getAspectRatio() const {

        return m_aspect_ratio;
    }

    void Camera3D::setViewRange(float min_dist, float max_dist) {
        /**  sets the range in which objects are going to be visible to the Camera3D
        * (their depth value will be between 0 and 1) */

        m_near_plane = min_dist;
        m_far_plane = max_dist;

    }

    void Camera3D::getViewRange(float& min_dist, float& max_dist) {

        min_dist = m_near_plane;
        max_dist = m_far_plane;

    }

    void Camera3D::setRotation(float pitch, float yaw, float roll, bool update_view) {

        m_pitch = pitch;
        m_yaw = yaw;
        m_roll = roll;
        m_use_angles = true;
        m_update_view_dir = true;

        if(update_view)
            updateView();
    }

    void Camera3D::setViewDir(const glm::vec3& view_dir, bool update_view) {
        /// usable for cameras without roll
        m_view_dir = view_dir;
        m_use_angles = false;
        m_update_view_dir = false;

        if(update_view)
            updateView();
    }

    const glm::vec3& Camera3D::getViewDir() {

        if(!m_update_view_dir) {
            // should be up to date
            return m_view_dir;
        } else {
            // needs to be calculated
            // still does not mean it can be used to calculate the view matrix since it does not says anything about roll
            // calculation taken from undicht 0.21.7

            m_view_dir.x = glm::cos(glm::radians(m_pitch)) * glm::sin(glm::radians(m_yaw));
            m_view_dir.y = - glm::sin(glm::radians(m_pitch));
            m_view_dir.z = - (glm::cos(glm::radians(m_pitch)) * glm::cos(glm::radians(m_yaw)));
            m_view_dir = glm::normalize(m_view_dir);

            m_update_view_dir = false;

            return m_view_dir;
        }

    }

    void Camera3D::setPosition(const glm::vec3& position, bool update_view) {

        m_position = position;

        if(update_view)
            updateView();
    }

    const glm::vec3& Camera3D::getPosition() const {

        return m_position;
    }

    const glm::mat4& Camera3D::getViewMat() {

        return m_view_mat;
    }

    const glm::mat4& Camera3D::getProjMat() {

        return m_proj_mat;
    }


    void Camera3D::updateView() {

        if(!m_use_angles) {
            // source: https://learnopengl.com/Getting-started/Camera

            m_view_mat = glm::lookAt(m_position, m_position + m_view_dir, glm::vec3(0,1,0));

        } else {
            // using euler angles + a quaternion to calculate the rotation of the camera
            // calculation taken (and modified for roll) from undicht 0.21.7

            // i think this would have worked in an older version of glm
            /*glm::quat rotation = glm::angleAxis(glm::radians(m_roll), glm::vec3(0,0,1));
            rotation *= glm::angleAxis(glm::radians(m_pitch), glm::vec3(1,0,0));
            rotation *= glm::angleAxis(glm::radians(m_yaw), glm::vec3(0,1,0));*/


            // this is what im going to try now, since i have no idea how quaternions work
            glm::quat rotation = glm::angleAxis(m_roll, glm::vec3(0,0,1));
            rotation = glm::cross(rotation, glm::angleAxis(m_pitch, glm::vec3(1,0,0)));
            rotation = glm::cross(rotation, glm::angleAxis(m_yaw, glm::vec3(0,1,0)));

            m_view_mat = glm::toMat4(rotation) * glm::translate(glm::mat4(1.0f), -1.0f * m_position);
        }

        m_view_uniform.setData(glm::value_ptr(m_view_mat), UND_MAT4F, true);

    }

    void Camera3D::updateProj() {

        if(m_use_perspective) {
            // creating the illusion of perspective

            m_proj_mat = glm::perspective(m_FoV, m_aspect_ratio, m_near_plane, m_far_plane);

        } else {
            // using an orthographic projection
            float right = m_aspect_ratio * m_FoV/2;
            float top =  m_FoV/(2 * m_aspect_ratio);

            m_proj_mat = glm::ortho( -1.0f * right, right, -1.0f * top, top, m_near_plane, m_far_plane);
        }


        m_proj_uniform.setData(glm::value_ptr(m_proj_mat), UND_MAT4F, true);

    }

} // undicht
