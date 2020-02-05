#include "glfw_mouse_input_watcher.h"
#include <core/types.h>



using namespace undicht::core;

namespace undicht {

    namespace window {

        namespace glfw {

            std::array<int, 8> MouseInputWatcher::s_mouse_buttons;
            int MouseInputWatcher::s_cursor_offset_x;
            int MouseInputWatcher::s_cursor_offset_y;
            int MouseInputWatcher::s_cursor_x;
            int MouseInputWatcher::s_cursor_y;
            int MouseInputWatcher::s_cursor_last_x;
            int MouseInputWatcher::s_cursor_last_y;
            bool first_mouse = true;


            ////////////////////////////////////////// glfw callbck functions /////////////////////////////////////////



            //to get the mouse position and movement since the last frame
            void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

                MouseInputWatcher::s_cursor_x = xpos;
                MouseInputWatcher::s_cursor_y = ypos;

            }

            void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

                MouseInputWatcher::s_mouse_buttons.at(button) = action; // whether the button was pressed or released
            }

            /////////////////////////////////////////////////// MouseInputWatcher ///////////////////////////////////////////////////

            MouseInputWatcher::MouseInputWatcher() {

            }

            MouseInputWatcher::~MouseInputWatcher() {

            }


            void MouseInputWatcher::updateChangedButtons() {
                /** creates a list of the buttons pressed/repeated/released since the last time this function was called
                * which can be retrieved with getChangedButton() */

                m_changed_buttons.clear();

                for(int i = 0; i < s_mouse_buttons.size(); i++) {

                    if(s_mouse_buttons[i] != m_last_button_states[i]) {
                        // when a button was just pressed / released

                        m_changed_buttons.push_back(i);

                    } else if(s_mouse_buttons[i] == UND_KEY_REPEATED ) {
                        // when a key is repeated

                        m_changed_buttons.push_back(i);
                    }

                }

                m_last_button_states = s_mouse_buttons;

            }


            const std::vector<int>& MouseInputWatcher::getChangedButtons() const {
                /** @return a list of all the buttons pressed/repeated/released
                * in the time since the last call to updateChangedButton */

                return m_changed_buttons;
            }

            int MouseInputWatcher::getButtonState(int button_id) const {
                /** @return the state (UND_KEY_PRESSED, UND_KEY_RELEASED ...) of the mouse button */

                return s_mouse_buttons.at(button_id);
            }

            void MouseInputWatcher::getCursorPosition(int& pos_x, int& pos_y) const {

                pos_x = s_cursor_x;
                pos_y = s_cursor_y;
            }

            void MouseInputWatcher::getCursorPosition(float& pos_x, float& pos_y) const {

                pos_x = float(s_cursor_x) / m_window->m_width * 2 - 1;
                pos_y = float(s_cursor_y) / m_window->m_height * -2 + 1;
            }


            void MouseInputWatcher::getCursorOffset(int& offset_x, int& offset_y) const {
                /** the distance moved by the cursor between the last two calls to updateCursorOffset() */

                offset_x = s_cursor_offset_x;
                offset_y = s_cursor_offset_y;
            }

            void MouseInputWatcher::getCursorOffset(float& offset_x, float& offset_y) const {
                /** the distance moved by the cursor between the last two calls to updateCursorOffset() */

                offset_x = float(s_cursor_offset_x) / m_window->m_width * 2;
                offset_y = float(s_cursor_offset_y) / m_window->m_height * -2;
            }

            void MouseInputWatcher::updateCursorOffset() {
                /** calculates the distance moved by the cursor
                * since the last call to this function */

                if(first_mouse) {
                    //no offset at the first time the mouse position is determined
                    MouseInputWatcher::s_cursor_last_x = s_cursor_x;
                    MouseInputWatcher::s_cursor_last_y = s_cursor_y;
                    first_mouse = false;
                }

                s_cursor_offset_x = s_cursor_x - s_cursor_last_x;
                s_cursor_offset_y = s_cursor_y - s_cursor_last_y;

                s_cursor_last_x = s_cursor_x;
                s_cursor_last_y = s_cursor_y;

            }


            void MouseInputWatcher::setWindow(window::Window* window) {

                m_window = (glfw::Window*)window->m_shared_lib_object;

                glfwSetCursorPosCallback(m_window->m_window, mouse_callback);
                glfwSetMouseButtonCallback(m_window->m_window, mouse_button_callback);

            }



            //////////////////// functions to load from the shared lib /////////

            SHARED_LIB_EXPORT implementation::MouseInputWatcher* createMouseInputWatcher() {

                return new glfw::MouseInputWatcher;
            }

            SHARED_LIB_EXPORT void copyMouseInputWatcher(implementation::MouseInputWatcher* c, implementation::MouseInputWatcher* o) {
                // copying the data from *o to *c

                *c = *o;
            }

            SHARED_LIB_EXPORT void deleteMouseInputWatcher(implementation::MouseInputWatcher* object) {

                delete (MouseInputWatcher*)object;
            }


        } // glfw

    } // window

} // undicht
