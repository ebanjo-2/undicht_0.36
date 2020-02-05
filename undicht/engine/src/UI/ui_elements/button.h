#ifndef BUTTON_H
#define BUTTON_H


#include "textured_ui_element.h"
#include <UI/font.h>
#include <UI/ui_elements/label.h>


namespace undicht {


    class Button : public TexturedUIElement {
        public:

            Label m_caption;

            Button();
            virtual ~Button();

            virtual void setCaption(const Label& label);


            /** @return true if the input was used by the ui element */
            virtual bool onKeyPress(int key_id, int key_state);

            /** @return true if the input was used by the ui element */
            virtual bool onMousePress(const glm::vec2& cursor_pos, int button_id, int button_state);

    };


} // undicht

#endif // BUTTON_H
