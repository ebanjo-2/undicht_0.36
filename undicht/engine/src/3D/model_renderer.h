#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include <graphics/renderer.h>
#include <3D/camera.h>
#include <3D/textured_model.h>
#include <string>


namespace undicht {

    class ModelRenderer : public graphics::Renderer {

        private:

            Camera3D* m_current_cam = 0;

            static graphics::Shader* s_shader;
            static const std::string s_shader_src;

        public:

            static void initialize();
            static void terminate();

        public:

            void submit(Camera3D* cam);

            void draw(TexturedModel& model);

            ModelRenderer();
            virtual ~ModelRenderer();


    };

} // undicht

#endif // MODELRENDERER_H
