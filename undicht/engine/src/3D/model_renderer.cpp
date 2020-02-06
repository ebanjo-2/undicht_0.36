#include "model_renderer.h"
#include <file_loading/file_reader.h>
#include <core/event_logger.h>

namespace undicht {

    using namespace graphics;
    using namespace core;

    Shader* ModelRenderer::s_shader;
    const std::string ModelRenderer::s_shader_src = "shader/model_shader.glsl";



    ModelRenderer::ModelRenderer() {
        //ctor

        if(s_shader) {

            ((Renderer*)this)->submit(s_shader);
        } else {

            EventLogger::storeNote(Note(UND_ERROR, "ERROR: please initialize the ModelRenderer before creating any instances of it", UND_CODE_ORIGIN));
        }

    }

    ModelRenderer::~ModelRenderer() {
        //dtor
    }

    void ModelRenderer::initialize() {

        s_shader = new Shader;

        // loading the shader source
        std::string file_path = getFilePath(replaceAll(UND_CODE_SRC_FILE, (char)92, '/')) + s_shader_src;
        std::string source_buffer;

        FileReader reader(file_path);
        s_shader->loadSource(reader.getAll(source_buffer));

    }


    void ModelRenderer::terminate() {

        delete s_shader;
    }

    void ModelRenderer::submit(Camera3D* cam) {

        m_current_cam = cam;
        s_shader->loadUniform(m_current_cam->m_proj_uniform);
        s_shader->loadUniform(m_current_cam->m_view_uniform);

    }

    void ModelRenderer::draw(TexturedModel& model) {

        Renderer::enableDepthTest(true);
        Renderer::enableBackFaceCulling(true);

        // loading the uniforms of the model
        s_shader->loadTexture(model.m_color);
        s_shader->loadUniform(model.m_scale_uniform);
        s_shader->loadUniform(model.m_transf_uniform);

        ((Renderer*)this)->submit(&model.m_mesh);
        ((Renderer*)this)->draw();

    }

} // undicht

