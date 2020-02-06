#include "geometry_stage_renderer.h"
#include <file_loading/file_reader.h>
#include <core/string_tools.h>
#include <core/event_logger.h>


namespace undicht {

    using namespace graphics;
    using namespace core;

    const std::string geometry_stage_shader_src = "shader/geometry_stage.glsl";

    graphics::Shader* GeometryStageRenderer::s_geometry_stage_shader = 0;


    GeometryStageRenderer::GeometryStageRenderer() {
        //ctor

        if(s_geometry_stage_shader) {

            ((Renderer*)this)->submit(s_geometry_stage_shader);

        } else {

            EventLogger::storeNote(Note(UND_ERROR, "ERROR: please initialize the GeometryStageRenderer before creating any instances of it", UND_CODE_ORIGIN));
        }
    }

    GeometryStageRenderer::~GeometryStageRenderer() {
        //dtor
    }

    void GeometryStageRenderer::initialize() {


        // loading the shader source
        std::string file_path = getFilePath(replaceAll(UND_CODE_SRC_FILE, (char)92, '/')) + geometry_stage_shader_src;
        std::string source_buffer;

        FileReader reader(file_path);

        s_geometry_stage_shader = new Shader;
        s_geometry_stage_shader->loadSource(reader.getAll(source_buffer));

    }


    void GeometryStageRenderer::terminate() {

        delete s_geometry_stage_shader;

    }

    void GeometryStageRenderer::submit(GBuffer* geometry_buffer) {

        ((Renderer*)this)->submit(geometry_buffer);

    }

    void GeometryStageRenderer::submit(Camera3D* cam) {

        std::cout << "loading camera uniforms" << "\n";

        m_current_cam = cam;
        s_geometry_stage_shader->loadUniform(m_current_cam->m_proj_uniform);
        s_geometry_stage_shader->loadUniform(m_current_cam->m_view_uniform);

    }

    void GeometryStageRenderer::draw(TexturedModel& model) {


        Renderer::enableDepthTest(true);
        Renderer::enableBackFaceCulling(true);


        std::cout << "before loading any uniforms" << "\n";
        // loading the uniforms of the model
        s_geometry_stage_shader->loadTexture(model.m_color);
        s_geometry_stage_shader->loadUniform(model.m_scale_uniform);
        s_geometry_stage_shader->loadUniform(model.m_transf_uniform);

                std::cout << "getting till here" << "\n";


        ((Renderer*)this)->submit(&model.m_mesh);
        ((Renderer*)this)->draw();

    }

} // undicht
