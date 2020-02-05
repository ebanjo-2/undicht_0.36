#include "graphics_lib.h"
#include <core/core.h>
#include <core/event_logger.h>
#include <graphics/vertex_buffer.h>
#include <graphics/shader.h>
#include <graphics/renderer.h>
#include <graphics/uniform.h>
#include <graphics/texture.h>
#include <graphics/frame_buffer.h>

using namespace undicht::core;

namespace undicht {

    namespace graphics {

        SHARED_LIB_API_IMPL(GraphicsLib::GraphicsLib()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(GraphicsLib::~GraphicsLib()) {
            //dtor
        }

        void GraphicsLib::initialize(window::GraphicsContext* context) {

            //calling the GraphicsLib::initialize in the shared lib via a non static function in that lib
            std::function<void(window::GraphicsContext*)> init;
            init = (void(*)(window::GraphicsContext*)) Core::s_video_lib.getFunction("initialize");
            init(context);

            // loading the functions to create objects from the library
            createVertexBuffer = (implementation::VertexBuffer*(*)()) Core::s_video_lib.getFunction("createVertexBuffer");
            copyVertexBuffer = (void(*)(implementation::VertexBuffer*,implementation::VertexBuffer*)) Core::s_video_lib.getFunction("copyVertexBuffer");
            deleteVertexBuffer = (void(*)(implementation::VertexBuffer*)) Core::s_video_lib.getFunction("deleteVertexBuffer");

            createShader = (implementation::Shader*(*)()) Core::s_video_lib.getFunction("createShader");
            copyShader = (void(*)(implementation::Shader*,implementation::Shader*)) Core::s_video_lib.getFunction("copyShader");
            deleteShader = (void(*)(implementation::Shader*)) Core::s_video_lib.getFunction("deleteShader");

            createRenderer = (implementation::Renderer*(*)()) Core::s_video_lib.getFunction("createRenderer");
            copyRenderer = (void(*)(implementation::Renderer*,implementation::Renderer*)) Core::s_video_lib.getFunction("copyRenderer");
            deleteRenderer = (void(*)(implementation::Renderer*)) Core::s_video_lib.getFunction("deleteRenderer");
            Renderer::s_set_viewport = (void(*)(int,int,int,int)) Core::s_video_lib.getFunction("setViewport");

            createUniform = (implementation::Uniform*(*)()) Core::s_video_lib.getFunction("createUniform");
            copyUniform = (void(*)(implementation::Uniform*,implementation::Uniform*)) Core::s_video_lib.getFunction("copyUniform");
            deleteUniform = (void(*)(implementation::Uniform*)) Core::s_video_lib.getFunction("deleteUniform");

            createTexture = (implementation::Texture*(*)()) Core::s_video_lib.getFunction("createTexture");
            copyTexture = (void(*)(implementation::Texture*,implementation::Texture*)) Core::s_video_lib.getFunction("copyTexture");
            deleteTexture = (void(*)(implementation::Texture*)) Core::s_video_lib.getFunction("deleteTexture");

            createFrameBuffer = (implementation::FrameBuffer*(*)()) Core::s_video_lib.getFunction("createFrameBuffer");
            copyFrameBuffer = (void(*)(implementation::FrameBuffer*,implementation::FrameBuffer*)) Core::s_video_lib.getFunction("copyFrameBuffer");
            deleteFrameBuffer = (void(*)(implementation::FrameBuffer*)) Core::s_video_lib.getFunction("deleteFrameBuffer");

            // loading static functions

            Renderer::s_set_viewport = (void(*)(int, int, int, int))Core::s_video_lib.getFunction("setViewport");
            Renderer::s_enable_depth_test = (void(*)(bool))Core::s_video_lib.getFunction("enableDepthTest");
            Renderer::s_enable_back_face_culling = (void(*)(bool))Core::s_video_lib.getFunction("enableBackFaceCulling");

        }

        void GraphicsLib::terminate() {

            ((void(*)())core::Core::s_video_lib.getFunction("terminate")) ();

        }

    } // graphics

} // undicht
