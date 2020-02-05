#include "shader.h"


namespace undicht {

    namespace graphics {


        SHARED_LIB_DEF_BASE_CLASS(Shader, createShader, copyShader, deleteShader);


        SHARED_LIB_API_IMPL(Shader::Shader()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(Shader::~Shader()) {
            //dtor
        }

        SHARED_LIB_API_IMPL(void Shader::loadSource(const std::string& source)){
            m_shared_lib_object->loadSource(source);
        }

        SHARED_LIB_API_IMPL(void Shader::loadUniform(const graphics::Uniform& u)){
            m_shared_lib_object->loadUniform(u);
        }

        SHARED_LIB_API_IMPL(void Shader::loadTexture(const graphics::Texture& t)){
            m_shared_lib_object->loadTexture(t);
        }

    } // graphics

} // undicht
