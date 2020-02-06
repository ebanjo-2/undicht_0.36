#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm/glm.hpp>
#include <graphics/uniform.h>


namespace undicht {


    class ModelRenderer;
    class GeometryStageRenderer;

    class Object3D {

        protected:

            friend ModelRenderer;
            friend GeometryStageRenderer;

            glm::vec3 m_position = glm::vec3(0.0f,0.0f,0.0f);
            glm::vec3 m_scale = glm::vec3(1.0f);

            // the objects rotation
            float m_pitch = 0;
            float m_yaw = 0;
            float m_roll = 0;

            glm::mat4 m_transf_mat; // the matrix combining rotation and position

            graphics::Uniform m_scale_uniform;
            graphics::Uniform m_transf_uniform;

        public:

            virtual void setPosition(const glm::vec3& position, bool update_transf = true);
            virtual const glm::vec3& getPosition() const;

            virtual void setScale(const glm::vec3& scale);
            virtual const glm::vec3& getScale();

            /// sets the rotation relative to the objects center
            virtual void setRotation(float pitch, float yaw = 0, float roll = 0, bool update_transf = true);
            virtual void getRotation(float& pitch, float& yaw, float& roll) const;

        public:

            virtual const glm::mat4& getTransfMat();

        protected:

            virtual void updateTransfMat();

        public:

            Object3D();
            virtual ~Object3D();


    };

} // undicht

#endif // OBJECT_H
