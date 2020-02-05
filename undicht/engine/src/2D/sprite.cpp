#include "sprite.h"

namespace undicht {

    Sprite::Sprite() {
        //ctor

        setName("color"); // the name of the sprite texture in the shader
    }

    Sprite::~Sprite() {
        //dtor
    }


    void Sprite::setPosition(const glm::vec3& pos) {

        m_position = pos;
    }


    void Sprite::setScale(const glm::vec2& scale) {

        m_scale = scale;
    }

    void Sprite::setUvScale(const glm::vec2& uv_scale) {

        m_uv_scale = uv_scale;
    }


    glm::vec3& Sprite::getPosition() {

        return m_position;
    }

    glm::vec2& Sprite::getScale() {

        return m_scale;
    }


} // undicht
