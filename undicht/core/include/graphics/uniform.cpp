#include "uniform.h"

namespace undicht {

    namespace graphics {

        SHARED_LIB_DEF_BASE_CLASS(Uniform, createUniform, copyUniform, deleteUniform);


        SHARED_LIB_API_IMPL(Uniform::Uniform()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(Uniform::~Uniform()) {
            //dtor
        }



        SHARED_LIB_API_IMPL(void Uniform::setData(const void* data, int type, bool copy_data)) {
            /** the uniform stores a single type,
            * see core/types.h for options */

            m_shared_lib_object->setData(data, type, copy_data);

        }

        SHARED_LIB_API_IMPL(void Uniform::setData(const void* data, core::BufferLayout layout, int num_of_elements)) {
            /** stores the data in a buffer accessable in the shader */

            m_shared_lib_object->setData(data, layout, num_of_elements);
        }

        SHARED_LIB_API_IMPL(void Uniform::setName(const std::string& name)) {
            /** sets the name with which the uniforms data can be accessed in the shader */

            m_shared_lib_object->setName(name);
        }

        SHARED_LIB_API_IMPL(const std::string& Uniform::getName() const){

            return m_shared_lib_object->getName();
        }

        SHARED_LIB_API_IMPL(int Uniform::getType() const){

            return m_shared_lib_object->getType();
        }

        SHARED_LIB_API_IMPL(const void* Uniform::getData() const){

            return m_shared_lib_object->getData();
        }

        SHARED_LIB_API_IMPL(const core::BufferLayout& Uniform::getLayout() const) {

            return m_shared_lib_object->getLayout();
        }


    } // graphics

} // undicht
