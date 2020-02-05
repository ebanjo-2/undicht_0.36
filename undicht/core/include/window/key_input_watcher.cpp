#include "key_input_watcher.h"

namespace undicht {

    namespace window {

        SHARED_LIB_DEF_BASE_CLASS( KeyInputWatcher, createKeyInputWatcher, copyKeyInputWatcher, deleteKeyInputWatcher);

        SHARED_LIB_API_IMPL(KeyInputWatcher::KeyInputWatcher()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(KeyInputWatcher::~KeyInputWatcher()) {
            //dtor
        }


        SHARED_LIB_API_IMPL(void KeyInputWatcher::updateChangedKeys()) {
            /** creates a list of the keys pressed/repeated/released since the last time this function was called
            * which can be retrieved with getChangedKeys() */

            m_shared_lib_object->updateChangedKeys();
        }


        SHARED_LIB_API_IMPL(const std::vector<int>& KeyInputWatcher::getChangedKeys() const) {
            /** @return a list of all the keys pressed/released
            * in the time since the last call to updateChangedKeys */

            return m_shared_lib_object->getChangedKeys();
        }

        SHARED_LIB_API_IMPL(int KeyInputWatcher::getKeyState(int key_id) const) {

            return m_shared_lib_object->getKeyState(key_id);
        }

        SHARED_LIB_API_IMPL(void KeyInputWatcher::setWindow(window::Window* window)) {

            m_shared_lib_object->setWindow(window);
        }


    } // window

} // undicht
