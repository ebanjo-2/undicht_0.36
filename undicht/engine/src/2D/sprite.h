#ifndef SPRITE_H
#define SPRITE_H

#include <graphics/texture.h>
#include <glm/glm/glm.hpp>


namespace undicht {


class Sprite : public graphics::Texture{
    public:

        glm::vec3 m_position; // sprites with higher z components will be drawn behind those with lower ones (range 0 - 1)
        glm::vec2 m_scale = glm::vec2(1,1);
        glm::vec2 m_uv_scale = glm::vec2(1,1);

        void setPosition(const glm::vec3& pos);
        void setScale(const glm::vec2& scale);
        void setUvScale(const glm::vec2& uv_scale);

        glm::vec3& getPosition();
        glm::vec2& getScale();

        Sprite();
        virtual ~Sprite();

};


} // undicht

#endif // SPRITE_H
