#ifndef LIGHTING_STAGE_RENDERER_H
#define LIGHTING_STAGE_RENDERER_H

#include <graphics/frame_buffer.h>
#include <graphics/renderer.h>

#include <3D/deferred_shading/g_buffer.h>
#include <3D/deferred_shading/point_light.h>
#include <3D/camera.h>


namespace undicht {

    class LightingStageRenderer : public graphics::Renderer {

        public:

            Camera3D* m_current_cam = 0;
            GBuffer* m_current_scene = 0;

            static graphics::Shader* s_shader;
            static const std::string s_shader_src;

        public:

            static void initialize();
            static void terminate();

        public:

            virtual void submit(Camera3D* cam);
            virtual void submit(graphics::FrameBuffer* fbo);
            virtual void submit(GBuffer* scene_geometry);

            /** draws the light into the scene */
            virtual void draw(const PointLight& l);

            /** draws the scene with the lights to the submitted frame buffer */
            virtual void draw();

            LightingStageRenderer();
            virtual ~LightingStageRenderer();

    };


} // undicht

#endif // LIGHTING_STAGE_RENDERER_H
