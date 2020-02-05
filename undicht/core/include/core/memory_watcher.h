#ifndef MEMORY_WATCHER_H
#define MEMORY_WATCHER_H

#include <vector>


namespace undicht {

    namespace core {

        class MemoryWatcher {
                /** a class to be used by other classes carrying
                * memory that needs to be deleted explicitly */
            public:
                // storing the user count of every object

                static std::vector<int> s_user_count;

            public:
                // to keep track of where the user count is stored

                int m_user_id = -1; // no user count jet

            public:
                // constructor / destructor

                MemoryWatcher();
                virtual ~MemoryWatcher();

            public:
                // automating the user count on copy

                void operator= (const MemoryWatcher& c);

                MemoryWatcher(const MemoryWatcher& c);

            public:
                // using the user count

                /** reserves a new user count & updates m_id
                * should be called when the data to be watched over is initialized or changed
                * when there was old data stored in the object it should also be checked if this data
                * has any users left */
                void createNewUserCount();

                /** deletes the user & returns the number of users left over
                * if no user (return: 0) is left, the data should be deleted */
                int deleteUser();


        };


    } //core

} // undicht

#endif // MEMORY_WATCHER_H
