#include "renderer.h"

namespace undicht {

    namespace graphics {

        std::function<void(int,int,int,int)> Renderer::s_set_viewport;
        std::function<void(bool)> Renderer::s_enable_depth_test;
        std::function<void(bool)> Renderer::s_enable_back_face_culling;

        SHARED_LIB_DEF_BASE_CLASS(Renderer, createRenderer, copyRenderer, deleteRenderer)

        SHARED_LIB_API_IMPL(Renderer::Renderer()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(Renderer::~Renderer()) {
            //dtor
        }

        SHARED_LIB_API_IMPL(void Renderer::submit(graphics::VertexBuffer* vbo)) {
            m_shared_lib_object->submit(vbo);
        }

        SHARED_LIB_API_IMPL(void Renderer::submit(graphics::Shader* shader)) {
            m_shared_lib_object->submit(shader);
        }

        SHARED_LIB_API_IMPL(void Renderer::submit(graphics::FrameBuffer* fbo)) {
            m_shared_lib_object->submit(fbo);
        }


        SHARED_LIB_API_IMPL(void Renderer::clearFramebuffer(float r, float g, float b, float alpha)){
            m_shared_lib_object->clearFramebuffer(r,g,b,alpha);
        }

        SHARED_LIB_API_IMPL(void Renderer::draw(unsigned int instance_count)) {
            m_shared_lib_object->draw(instance_count);
        }

        SHARED_LIB_API_IMPL(void Renderer::setViewport(int width, int height, int offset_x, int offset_y)){
            s_set_viewport(width, height, offset_x, offset_y);
        }

        SHARED_LIB_API_IMPL(void Renderer::enableDepthTest(bool enable)) {
            s_enable_depth_test(enable);
        }

        SHARED_LIB_API_IMPL(void Renderer::enableBackFaceCulling(bool enable)) {
            s_enable_back_face_culling(enable);
        }




    } // graphics

} // undicht
