#ifndef GLFW_KEY_INPUT_WATCHER_H
#define GLFW_KEY_INPUT_WATCHER_H

#include <core/shared_lib_class.h>

#include <window/key_ids.h>
#include <window/key_input_watcher.h>
#include "glfw_window.h"

namespace undicht {

    namespace window {

        namespace glfw {

            class KeyInputWatcher : public implementation::KeyInputWatcher {
                public:

                    static std::array<int, 512> s_key_states;
                    std::array<int, 512> m_last_key_states;

                    std::vector<int> m_changed_keys;

                    glfw::Window* m_window = 0; // the window that receives the key presses

                    /** creates a list of the keys pressed/repeated/released since the last time this function was called
                    * which can be retrieved with getChangedKeys() */
                    virtual void updateChangedKeys();

                    /** @return a list of all the keys pressed/repeated/released
                    * in the time since the last call to the function */
                    virtual const std::vector<int>& getChangedKeys() const;

                    virtual int getKeyState(int key_id) const;

                    virtual void setWindow(window::Window* window);

                    KeyInputWatcher();
                    virtual ~KeyInputWatcher();
            };


        } // glfw

    } // window

} // undicht

#endif // GLFW_KEY_INPUT_WATCHER_H
