#ifndef GL33_RENDERER_H
#define GL33_RENDERER_H

#include <graphics/renderer.h>
#include "gl33_vertex_buffer.h"
#include "gl33_shader.h"
#include "gl33_frame_buffer.h"


namespace undicht {

    namespace graphics {

        namespace gl33 {


            class Renderer : public implementation::Renderer {

                public:
                    // storing the last submissions

                    VertexBuffer* m_current_vbo = 0;
                    Shader* m_current_shader = 0;
                    FrameBuffer* m_current_fbo = 0;

                    static bool s_depth_test_enabled;
                    static bool s_culling_enabled;

                public:
                    // opengl only functions

                    /// binding the submitted fbo
                    void useFbo();

                public:

                    virtual void submit(graphics::VertexBuffer* vbo);
                    virtual void submit(graphics::Shader* shader);
                    virtual void submit(graphics::FrameBuffer* fbo);

                    virtual void clearFramebuffer(float r = 1, float g = 1, float b = 1, float alpha = 1);
                    virtual void draw(unsigned int instance_count = 1);

                    static void setViewport(int width, int height, int offset_x = 0, int offset_y = 0);
                    static void enableDepthTest(bool enable = true);
                    static void enableBackFaceCulling(bool enable = true);


                    Renderer();
                    virtual ~Renderer();

            };

        } // gl33

    } // graphics

} // undicht

#endif // GL33_RENDERER_H
