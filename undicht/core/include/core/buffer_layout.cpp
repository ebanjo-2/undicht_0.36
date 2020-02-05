#include <core/buffer_layout.h>


namespace undicht {

    namespace core {

        unsigned BufferLayout::getTotalSize() {


            unsigned int total_size = 0;

            for(int& type : m_types ) {

                total_size += getSizeOfType(type);

            }

            return total_size;
        }


    } // core

} // undicht
