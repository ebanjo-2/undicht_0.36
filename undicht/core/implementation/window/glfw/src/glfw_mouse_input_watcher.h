#ifndef GLFW_MOUSE_INPUT_WATCHER_H
#define GLFW_MOUSE_INPUT_WATCHER_H


#include <core/shared_lib_class.h>

#include <window/key_ids.h>
#include <window/mouse_input_watcher.h>
#include "glfw_window.h"

namespace undicht {

    namespace window {

        namespace glfw {

            class MouseInputWatcher : public implementation::MouseInputWatcher {
                public:

                    glfw::Window* m_window = 0; // the window that receives the key presses

                    static std::array<int, 8> s_mouse_buttons;
                    static int s_cursor_offset_x;
                    static int s_cursor_offset_y;
                    static int s_cursor_x;
                    static int s_cursor_y;
                    static int s_cursor_last_x;
                    static int s_cursor_last_y;

                    // to track the changed buttons
                    std::array<int, 8> m_last_button_states;
                    std::vector<int> m_changed_buttons;

                    /** creates a list of the buttons pressed/repeated/released since the last time this function was called
                    * which can be retrieved with getChangedButton() */
                    virtual void updateChangedButtons();

                    /** @return a list of all the buttons pressed/repeated/released
                    * in the time since the last call to updateChangedButton */
                    virtual const std::vector<int>& getChangedButtons() const;

                    /** @return the state (UND_KEY_PRESSED, UND_KEY_RELEASED ...) of the mouse button */
                    virtual int getButtonState(int button_id) const;

                    /** the pixel position of the cursor gets stored */
                    virtual void getCursorPosition(int& pos_x, int& pos_y) const;

                    /** the relative position (0.0f to 1.0f) gets stored */
                    virtual void getCursorPosition(float& pos_x, float& pos_y) const;

                    /** the distance moved by the cursor between the last two calls to updateCursorOffset() */
                    virtual void getCursorOffset(int& offset_x, int& offset_y) const;

                    /** the distance moved by the cursor between the last two calls to updateCursorOffset()
                    * in the relative coordinate system */
                    virtual void getCursorOffset(float& offset_x, float& offset_y) const;

                    /** calculates the distance moved by the cursor
                    * since the last call to this function */
                    virtual void updateCursorOffset();

                    virtual void setWindow(window::Window* window);

                    MouseInputWatcher();
                    virtual ~MouseInputWatcher();
            };


        } // glfw

    } // window

} // undicht


#endif // GLFW_MOUSE_INPUT_WATCHER_H
