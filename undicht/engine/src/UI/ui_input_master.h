#ifndef UI_INPUT_MASTER_H
#define UI_INPUT_MASTER_H

#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>


namespace undicht {

    class UIElement;

    class UIInputMaster {
            /** the class that forwards user input to the ui elements linked to it */
        public:

            std::vector<UIElement*> m_elements; // also determining the order in which elements are going to receive user input

            /** the ui element gets added into the front */
            void addUIElement(UIElement* e);
            void remUIElement(UIElement* e);

            // changing the order of the ui elements
            void moveToFront(UIElement* e);
            void moveToBack(UIElement* e);
            void moveForward(UIElement* e);
            void moveBackward(UIElement* e);

            void forwardInput(const window::KeyInputWatcher& key_input, const window::MouseInputWatcher& mouse_input);

            UIInputMaster();
            virtual ~UIInputMaster();

    };

} // undicht

#endif // UI_INPUT_MASTER_H
