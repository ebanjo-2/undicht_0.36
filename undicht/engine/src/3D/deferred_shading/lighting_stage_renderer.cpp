#include "lighting_stage_renderer.h"

#include <file_loading/file_reader.h>

namespace undicht {

    using namespace graphics;

    graphics::Shader* LightingStageRenderer::s_shader = 0;

    const std::string LightingStageRenderer::s_shader_src = "shader/lighting_stage.glsl";

    LightingStageRenderer::LightingStageRenderer() {
        //ctor
    }

    LightingStageRenderer::~LightingStageRenderer() {
        //dtor
    }

    void LightingStageRenderer::initialize() {

        // loading the shader source
        s_shader = new Shader;

        std::string buffer;
        FileReader reader(s_shader_src);
        s_shader->loadSource(reader.getAll(buffer));


    }

    void LightingStageRenderer::terminate() {

        delete s_shader;

    }

    void LightingStageRenderer::submit(Camera3D* cam) {

        m_current_cam = cam;

    }


    void LightingStageRenderer::submit(FrameBuffer* fbo) {

        ((Renderer*)this)->submit(fbo);

    }


    void LightingStageRenderer::submit(GBuffer* scene_geometry) {

        m_current_scene = scene_geometry;
    }

    void LightingStageRenderer::draw(const PointLight& l) {
        /** adds the light to the scene */

        // loading the scene geometry to the shader


    }

    void LightingStageRenderer::draw() {

    }

} // undicht
