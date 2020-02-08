#include "button.h"

#include <core/types.h>
#include <window/key_ids.h>
#include "label.h"


namespace undicht {


    using namespace core;
    using namespace window;


    Button::Button() {
        //ctor
        m_child_elements.push_back(&m_caption);
        m_caption.setParent(this);
    }

    Button::~Button() {
        //dtor
    }

    void Button::setCaption(const Label& label) {

        m_caption = label;
        m_caption.setParent(this);
        m_caption.setPosition(glm::vec2(-0.4, 0));
    }


    bool Button::onKeyPress(int key_id, int key_state) {
        /** @return true if the input was used by the ui element */

        return false;
    }

    bool Button::onMousePress(const glm::vec2& cursor_pos, int button_id, int button_state) {
        /** @return true if the input was used by the ui element */

        int width, height;
        m_texture.getSize(width, height);

        std::cout << "texture size: " << width << " " << height << "\n";

        if((width != 1) || (height != 1)) {
            // no button press for u (no changing the color)
            return false;
        }

        // testing if the button was pressed
        glm::vec2 upper_left = getPositionOnScreen() + (getSizeOnScreen() * glm::vec2(-0.5, 0.5));
        glm::vec2 lower_right = upper_left + getSizeOnScreen() * glm::vec2(1, -1);


        if(cursor_pos.x > upper_left.x && cursor_pos.x < lower_right.x) {

            if(cursor_pos.y < upper_left.y && cursor_pos.y > lower_right.y) {

                if(button_id == UND_MOUSE_1 && button_state == UND_KEY_PRESSED) {

                    unsigned char orange[] = {255, 125, 0};
                    m_texture.setData((char*)orange, sizeof(orange));

                } else {

                    unsigned char black[] = {0, 0, 0};
                    m_texture.setData((char*)black, sizeof(black));

                }

                return true;
            }

        }

        return false;
    }

} // undicht
