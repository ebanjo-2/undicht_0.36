#ifndef KEY_INPUT_WATCHER_H
#define KEY_INPUT_WATCHER_H

#include <core/shared_lib_class.h>
#include <window/key_ids.h>
#include <window/window.h>

namespace undicht {

    namespace window {

        SHARED_LIB_DECL_BASE_CLASS(KeyInputWatcher, KeyInputWatcherBase, createKeyInputWatcher, copyKeyInputWatcher, deleteKeyInputWatcher);

        SHARED_LIB_CLASS(class KeyInputWatcher : public KeyInputWatcherBase {
            public:

                /** creates a list of the keys pressed/repeated/released since the last time this function was called
                * which can be retrieved with getChangedKeys() */
                virtual void updateChangedKeys();

                /** @return a list of all the keys pressed/repeated/released
                * in the time since the last call to getChangedKeys */
                virtual const std::vector<int>& getChangedKeys() const;


                virtual int getKeyState(int key_id) const;

                virtual void setWindow(window::Window* window);

                KeyInputWatcher();
                virtual ~KeyInputWatcher();
        };)

    } // window

} // undicht

#endif // KEY_INPUT_WATCHER_H
