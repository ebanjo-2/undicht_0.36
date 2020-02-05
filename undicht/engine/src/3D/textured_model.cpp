#include "textured_model.h"

namespace undicht {

    TexturedModel::TexturedModel() {
        //ctor

        m_color.setName("color");
        m_scale_uniform.setName("scale");
        m_transf_uniform.setName("model");

        setScale(glm::vec3(0.1f));
    }

    TexturedModel::~TexturedModel() {
        //dtor
    }

} // undicht
