#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include <graphics/texture.h>
#include <graphics/vertex_buffer.h>
#include <3D/object.h>


namespace undicht {


    class TexturedModel : public Object3D {
        public:

            graphics::Texture m_color;
            graphics::VertexBuffer m_mesh;

            TexturedModel();
            virtual ~TexturedModel();

    };

} // undicht

#endif // TEXTUREDMODEL_H
