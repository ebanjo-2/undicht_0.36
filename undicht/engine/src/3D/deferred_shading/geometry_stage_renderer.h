#ifndef GEOMETRYSTAGERENDERER_H
#define GEOMETRYSTAGERENDERER_H


#include <graphics/renderer.h>
#include <graphics/shader.h>

#include <3D/deferred_shading/g_buffer.h>
#include <3D/camera.h>
#include <3D/textured_model.h>



namespace undicht {


    class GeometryStageRenderer {
        /** a renderer that can be used to draw a scene into a geometry buffer
        * so that deferred shading can be applied to it */
        protected:


            static graphics::Shader* s_geometry_stage_shader;
            Camera3D* m_current_cam = 0;

        public:

            static void initialize();
            static void terminate();

        public:

            virtual void submit(GBuffer* geometry_buffer);

            virtual void submit(Camera3D* cam);

            virtual void draw(TexturedModel& model);

            GeometryStageRenderer();
            virtual ~GeometryStageRenderer();

    };


} // undicht

#endif // GEOMETRYSTAGERENDERER_H
