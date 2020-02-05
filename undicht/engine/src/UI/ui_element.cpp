#include "ui_element.h"


namespace undicht {

    UIElement::UIElement() {
        //ctor
    }

    UIElement::UIElement(UIInputMaster* input) : m_input(input) {

        if(m_input) {
            m_input->addUIElement(this);
        }

    }

    UIElement::UIElement(UIElement* parent) : m_parent_element(parent) {
        //ctor

    }

    UIElement::~UIElement() {
        //dtor

        if(m_input) {
            m_input->remUIElement(this);
        }

    }

    void UIElement::setParent(UIElement* parent_element) {

        m_parent_element = parent_element;
    }

    UIElement* UIElement::getParent() const {

        return m_parent_element;
    }


    void UIElement::setPosition(const glm::vec2& pos) {
        /** setting the position relative to the parent element */

        m_pos = pos;
    }


    const glm::vec2& UIElement::getPosition() const {
        /** @return the position relative to the parent element */

        return m_pos;
    }


    glm::vec2 UIElement::getPositionOnScreen() const {
        /** @return the actual position of this element on the screen */

        glm::vec2 screen_pos = m_pos;

        UIElement* parent = getParent();

        while(parent) {
            screen_pos *= parent->getSize();
            screen_pos += parent->getPosition();

            parent = parent->getParent();
        }

        return screen_pos;
    }

    void UIElement::setSize(const glm::vec2& size) {
        /** setting the size relative to the parent element */

        m_size = size;
    }

    const glm::vec2& UIElement::getSize() const {
        /** @return the size relative to the parent element */

        return m_size;
    }

    glm::vec2 UIElement::getSizeOnScreen() const {
        /** @return the actual size of this element on the screen */

        glm::vec2 screen_size = m_size;

        UIElement* parent = getParent();

        while(parent) {
            screen_size *= parent->getSize();

            parent = parent->getParent();
        }

        return screen_size;
    }

    ////////////////////////////////////// user input functions (to be implemented by derived classes) //////////////////////////////////////////



    bool UIElement::onKeyPress(int key_id, int key_state) {
        /** @return true if the input was used by the ui element */

        // to be implemented by derived classes

        return false;
    }


    bool UIElement::onMousePress(const glm::vec2& cursor_pos, int button_id, int button_state) {
        /** @return true if the input was used by the ui element */

        // to be implemented by derived classes

        return false;
    }

    void UIElement::onWindowResize(int width, int height) {

        // to be implemented by derived classes
    }

    ////////////////////////////////////// to determine how the element should be treated when drawing it //////////////////////////////////////

    int UIElement::getType() const {

        return m_type;
    }

} // undicht
