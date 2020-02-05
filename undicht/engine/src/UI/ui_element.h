#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <vector>
#include <glm/glm/glm.hpp>
#include "ui_input_master.h"
#include <UI/ui_element_types.h>

namespace undicht {

    class UIRenderer;

    class UIElement {
        /** the base class to all ui elements
        * implementing a layer system by enabling ui elements to hold other elements */

        public:

            friend UIRenderer;

            UIInputMaster* m_input = 0;

            // the type that determines how the element should be rendered
            // see UI/ui_element_types.h
            int m_type = 0;

            UIElement* m_parent_element = 0;
            std::vector<UIElement*> m_child_elements;

            virtual void setParent(UIElement* parent_element);

            virtual UIElement* getParent() const;

        public:

            glm::vec2 m_pos = glm::vec2(0,0); // position (upper left) relative to the parent element with vec2(1,1) being the upper right corner of the parent element

            /** setting the position relative to the parent element */
            virtual void setPosition(const glm::vec2& pos);

            /** @return the position relative to the parent element */
            virtual const glm::vec2& getPosition() const;

            /** @return the actual position of this element on the screen */
            virtual glm::vec2 getPositionOnScreen() const;

        public:

            glm::vec2 m_size = glm::vec2(1,1); // size relative to the the parent element, with glm::vec2(1,1) having the same size as the parent element

            /** @param the size describes the total width and height of the element
            * setting the size relative to the parent element */
            virtual void setSize(const glm::vec2& size);

            /** @return the size relative to the parent element */
            virtual const glm::vec2& getSize() const;

            /** @return the actual size of this element on the screen */
            virtual glm::vec2 getSizeOnScreen() const;

        public:
            // user input functions (to be implemented by derived classes)
            // only the "highest" parent receives the input and is responsible to dispatch it to its childs

            /** @return true if the input was used by the ui element */
            virtual bool onKeyPress(int key_id, int key_state);

            /** @return true if the input was used by the ui element */
            virtual bool onMousePress(const glm::vec2& cursor_pos, int button_id, int button_state);

            virtual void onWindowResize(int width, int height);

        public:

            // to determine how the element should be treated when drawing it
            int getType() const;


        public:

            UIElement();
            UIElement(UIElement* parent);
            UIElement(UIInputMaster* input); // only the "highest" parent receives the input and is responsible to dispatch it to its childs
            virtual ~UIElement();



    };

} // undicht

#endif // UIELEMENT_H
