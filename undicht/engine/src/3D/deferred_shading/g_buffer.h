#ifndef GBUFFER_H
#define GBUFFER_H


#include <graphics/frame_buffer.h>


namespace undicht {

    class GBuffer : public graphics::FrameBuffer{
        public:
            /** @brief a geometry buffer holding the geometry of the visible scene
            * including its albedo, depth, normals, lighting parameters, ... */

            graphics::Texture m_albedo;
            graphics::Texture m_depth;

            void initialize();


            GBuffer();
            virtual ~GBuffer();

    };


} // undicht

#endif // GBUFFER_H
