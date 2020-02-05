#include "ui_input_master.h"
#include "ui_element.h"

using namespace undicht::window;

namespace undicht {

    UIInputMaster::UIInputMaster() {
        //ctor
    }

    UIInputMaster::~UIInputMaster() {
        //dtor
    }


    void UIInputMaster::addUIElement(UIElement* e) {

        m_elements.push_back(e);

    }

    void UIInputMaster::remUIElement(UIElement* e) {

        for(int i = 0; i < m_elements.size(); i++) {

            if(m_elements.at(i) == e) {

                m_elements.erase(m_elements.begin() + i);
                return;
            }

        }

    }

    void UIInputMaster::forwardInput(const KeyInputWatcher& key_input, const window::MouseInputWatcher& mouse_input) {

        std::vector<int> changed_keys = key_input.getChangedKeys();
        std::vector<int> changed_buttons = mouse_input.getChangedButtons();
        glm::vec2 mouse_pos;
        mouse_input.getCursorPosition(mouse_pos.x, mouse_pos.y);

        // forwarding key input
        for(int& key : changed_keys) {

            for(int i = 0; i < m_elements.size(); i++) {
                if(m_elements.at(m_elements.size() - i - 1)->onKeyPress(key, key_input.getKeyState(key))) {

                    break;
                }
            }
        }

        // forwarding mouse input
        for(int& button : changed_buttons) {

            for(int i = 0; i < m_elements.size(); i++) {
                if(m_elements.at(m_elements.size() - i - 1)->onMousePress(mouse_pos, button, mouse_input.getButtonState(button))) {

                    break;
                }
            }
        }


    }


} // undicht
