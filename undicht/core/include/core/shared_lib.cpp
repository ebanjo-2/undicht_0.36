#include <core/shared_lib.h>
#include <core/event_logger.h>
#include <core/string_tools.h>


namespace undicht {

    namespace core {

        SharedLib::SharedLib() {

        }

        SharedLib::SharedLib(const std::string& file_name) {
            open(file_name);
        }

        SharedLib::~SharedLib() {
            close();
        }

        void SharedLib::open(const std::string& file_name) {
            m_file_name = file_name;
            m_handle = SHARED_LIB_OPEN(file_name.data());

            auto dl_error = SHARED_LIB_ERROR;

            if(dl_error) {
                EventLogger::storeNote(Note(UND_ERROR, dl_error, UND_CODE_ORIGIN));
                EventLogger::storeNote(Note(UND_MESSAGE, std::string("failed to open: ") + file_name, UND_CODE_ORIGIN));
            }

        }

        void SharedLib::close() {
            if(m_handle) {
                SHARED_LIB_CLOSE(m_handle);
                m_handle = 0;
            }
        }

        void* SharedLib::getFunction(const std::string& name) {
            /** returns a pointer to the requested function
            * the function should be exported with SHARED_LIB_EXPORT */

            void* func = (void*)SHARED_LIB_LOAD(m_handle, name.data());

            if(!func) {
                auto error = SHARED_LIB_ERROR;
                if(error) {
                    EventLogger::storeNote(Note(UND_ERROR,error, UND_CODE_ORIGIN));
                }
            }

            return func;
        }

    } // core

} // undicht
