#include "mouse_input_watcher.h"

namespace undicht {

    namespace window {

        SHARED_LIB_DEF_BASE_CLASS( MouseInputWatcher, createMouseInputWatcher, copyMouseInputWatcher, deleteMouseInputWatcher);

        SHARED_LIB_API_IMPL(MouseInputWatcher::MouseInputWatcher()) {
            //ctor
        }


        SHARED_LIB_API_IMPL(MouseInputWatcher::~MouseInputWatcher()) {
            //dtor
        }


        SHARED_LIB_API_IMPL(void MouseInputWatcher::updateChangedButtons()) {
            /** creates a list of the buttons pressed/repeated/released since the last time this function was called
            * which can be retrieved with getChangedButton() */

            m_shared_lib_object->updateChangedButtons();
        }


        SHARED_LIB_API_IMPL(const std::vector<int>& MouseInputWatcher::getChangedButtons() const) {
            /** @return a list of all the buttons pressed/repeated/released
            * in the time since the last call to updateChangedButton */

            return m_shared_lib_object->getChangedButtons();
        }

        SHARED_LIB_API_IMPL(int MouseInputWatcher::getButtonState(int button_id) const) {
            /** @return the state (UND_KEY_PRESSED, UND_KEY_RELEASED ...) of the mouse button */

            return m_shared_lib_object->getButtonState(button_id);
        }

        SHARED_LIB_API_IMPL(void MouseInputWatcher::getCursorPosition(int& pos_x, int& pos_y) const) {

            m_shared_lib_object->getCursorPosition(pos_x, pos_y);
        }

        SHARED_LIB_API_IMPL(void MouseInputWatcher::getCursorPosition(float& pos_x, float& pos_y) const) {

            m_shared_lib_object->getCursorPosition(pos_x, pos_y);
        }


        SHARED_LIB_API_IMPL(void MouseInputWatcher::getCursorOffset(int& offset_x, int& offset_y) const) {
            /** the distance moved by the cursor between the last two calls to updateCursorOffset() */

            m_shared_lib_object->getCursorOffset(offset_x, offset_y);
        }

        SHARED_LIB_API_IMPL(void MouseInputWatcher::getCursorOffset(float& offset_x, float& offset_y) const) {
            /** the distance moved by the cursor between the last two calls to updateCursorOffset() */

            m_shared_lib_object->getCursorOffset(offset_x, offset_y);
        }


        SHARED_LIB_API_IMPL(void MouseInputWatcher::updateCursorOffset()) {
            /** calculates the distance moved by the cursor
            * since the last call to this function */

            m_shared_lib_object->updateCursorOffset();
        }

        SHARED_LIB_API_IMPL(void MouseInputWatcher::setWindow(window::Window* window)) {

            m_shared_lib_object->setWindow(window);
        }


    } // window

} // undicht
