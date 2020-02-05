#include "glfw_key_input_watcher.h"
#include <GLFW/glfw3.h>

#include <core/event_logger.h>
#include <core/types.h>

using namespace undicht::core;

namespace undicht {

    namespace window {

        namespace glfw {

            std::array<int, 512> KeyInputWatcher::s_key_states;
            void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

            KeyInputWatcher::KeyInputWatcher() {

            }

            KeyInputWatcher::~KeyInputWatcher() {

            }


            void KeyInputWatcher::updateChangedKeys() {
                /** creates a list of the keys pressed/repeated/released since the last time this function was called
                * which can be retrieved with getChangedKeys() */

                m_changed_keys.clear();

                for(int i = 0; i < s_key_states.size(); i++) {

                    if(s_key_states[i] != m_last_key_states[i]) {
                        // when a key was just pressed / released

                        m_changed_keys.push_back(i);

                    } else if(s_key_states[i] == UND_KEY_RELEASED) {
                        // when a key is repeated

                        m_changed_keys.push_back(i);

                    }

                }

                m_last_key_states = s_key_states;

            }

            const std::vector<int>& KeyInputWatcher::getChangedKeys() const {

                return m_changed_keys;
            }


            int KeyInputWatcher::getKeyState(int key_id) const {

                if(m_window) {

                    switch (glfwGetKey(m_window->m_window, key_id)) {
                        case GLFW_PRESS:
                            return UND_KEY_PRESSED;
                        case GLFW_REPEAT:
                            return UND_KEY_REPEATED;
                        case GLFW_RELEASE:
                            return UND_KEY_RELEASED;
                    }

                } else {
                    EventLogger::storeNote(Note(UND_ERROR, "KeyInputWatcher has no window set", UND_CODE_ORIGIN));
                    return UND_TYPE_UNAVAILABLE;
                }

            }

            void KeyInputWatcher::setWindow(window::Window* window) {

                m_window = (glfw::Window*)window->m_shared_lib_object;
                glfwSetKeyCallback(m_window->m_window, key_callback);

            }

            ///////////////////// glfw callback functions /////////////////////////////

            void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

                KeyInputWatcher::s_key_states.at(key) = action;

            }



            //////////////////// functions to load from the shared lib /////////

            SHARED_LIB_EXPORT implementation::KeyInputWatcher* createKeyInputWatcher() {
                return new glfw::KeyInputWatcher;
            }

            SHARED_LIB_EXPORT void copyKeyInputWatcher(implementation::KeyInputWatcher* c, implementation::KeyInputWatcher* o) {
                // copying the data from *o to *c

                *c = *o;
            }

            SHARED_LIB_EXPORT void deleteKeyInputWatcher(implementation::KeyInputWatcher* object) {

                delete (KeyInputWatcher*)object;
            }


        } // glfw

    } // window

} // undicht
