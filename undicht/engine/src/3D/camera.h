#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include <glm/glm/glm.hpp>
#include <3D/object.h>
#include <graphics/uniform.h>

namespace undicht {

    class ModelRenderer;


    class Camera3D : protected Object3D {

        protected:

            friend ModelRenderer;

            float m_FoV = 100;
            float m_aspect_ratio = 1.6f;
            float m_near_plane = 0.1f;
            float m_far_plane = 1000.0f;

            bool m_use_perspective = true;

            glm::vec3 m_view_dir = glm::vec3(0.0f, 0.0f, -1.0f);

            bool m_use_angles = true; // whether to use the view dir vector or the euler angles to represent the cameras rotation
            bool m_update_view_dir = true; // whether to update the view dir before it can be returned by getViewDir()

            glm::mat4 m_view_mat;
            glm::mat4 m_proj_mat;

            graphics::Uniform m_view_uniform;
            graphics::Uniform m_proj_uniform;


        public:

            /** whether to create the illusion of perspective
            * (making objects further away appear smaller) */
            void setProjectionMode(bool perspective);
            bool getProjectionMode() const;

            /** if the camera is orthographic, this sets the width of the view */
            void setFoV(float fov);
            float getFoV() const;

            /** the ratio between the width and the height of the field of view  */
            void setAspectRatio(float aspect_ratio);
            float getAspectRatio() const;

            /**  sets the range in which objects are going to be visible to the camera
            * (their depth value will be between 0 and 1) */
            void setViewRange(float min_dist, float max_dist);
            void getViewRange(float& min_dist, float& max_dist);

        public:

            void setRotation(float pitch, float yaw, float roll = 0, bool update_view = true);

            /// usable for cameras without roll
            void setViewDir(const glm::vec3& view_dir, bool update_view = true);
            const glm::vec3& getViewDir();

            void setPosition(const glm::vec3& position, bool update_view = true);
            const glm::vec3& getPosition() const;

        public:

            const glm::mat4& getViewMat();
            const glm::mat4& getProjMat();

        protected:

            void updateView();
            void updateProj();

        public:

            Camera3D();
            virtual ~Camera3D();

    };

} // undicht

#endif // CAMERA_3D_H
