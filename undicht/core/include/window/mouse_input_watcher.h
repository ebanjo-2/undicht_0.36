#ifndef MOUSE_INPUT_WATCHER_H
#define MOUSE_INPUT_WATCHER_H

#include <core/shared_lib_class.h>
#include <window/key_ids.h>
#include <window/window.h>

namespace undicht {

    namespace window {

        SHARED_LIB_DECL_BASE_CLASS(MouseInputWatcher, MouseInputWatcherBase, createMouseInputWatcher, copyMouseInputWatcher, deleteMouseInputWatcher);

        SHARED_LIB_CLASS(class MouseInputWatcher : public MouseInputWatcherBase {
            public:

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

                /** the relative position (-1.0f to 1.0f) gets stored */
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
        };)

    } // window

} // undicht

#endif // MOUSE_INPUT_WATCHER_H
