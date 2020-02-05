#ifndef SHARED_ID_H
#define SHARED_ID_H

#include "memory_watcher.h"


namespace undicht {

    namespace core {

        class SharedID : private MemoryWatcher{
            /** a class that stores the id to an object which may be referenced in multiple objects
            * and needs to be deleted when the last referencing object is destroyed */
            public:

                unsigned int m_id = 0;

                /** to be called when an object referencing the id is destroyed
                * @return true when the object being destroyed is the last one referencing the id */
                bool removeUser();

                void setID(unsigned int id);

                unsigned int& getID();

                void operator= (unsigned int id);
                operator unsigned int();

                SharedID();
                SharedID(unsigned int id);
                virtual ~SharedID();


        };

    } // core

} // undicht

#endif // SHARED_ID_H
