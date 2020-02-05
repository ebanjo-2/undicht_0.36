#ifndef TEXTUREDUIELEMENT_H
#define TEXTUREDUIELEMENT_H

#include <graphics/texture.h>
#include <UI/ui_element.h>


namespace undicht {


    class TexturedUIElement : public UIElement {
        public:

            graphics::Texture m_texture;

            const graphics::Texture& getTexture() const ;

            virtual bool onKeyPress(int key_id, int key_state);

            TexturedUIElement();
            virtual ~TexturedUIElement();


    };


} // undicht

#endif // TEXTUREDUIELEMENT_H
