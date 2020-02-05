#include <core/memory_watcher.h>
#include <iostream>


namespace undicht {

    namespace core {

        std::vector<int> MemoryWatcher::s_user_count;


        /////////////////////////////////////////// constructor / destructor /////////////////////////////////////////


        MemoryWatcher::MemoryWatcher() {
            //ctor
        }

        MemoryWatcher::~MemoryWatcher() {
            //dtor
        }


        ///////////////////////////////////// automating the user count on copy ////////////////////////////////////////


        void MemoryWatcher::operator= (const MemoryWatcher& c) {



            if(s_user_count.size() > (unsigned int) c.m_user_id) {

                s_user_count.at(c.m_user_id) += 1;
                m_user_id = c.m_user_id;

                //std::cout << "copying data of user " << m_user_id << "\n";
                //std::cout << "user count: " << s_user_count.at(c.m_user_id) << "\n";
            } else {

                if(c.m_user_id != -1) {

                    std::cout << "failed to add user to " << c.m_user_id << "\n";
                    std::cout << "user count does not exist " << "\n";

                }

            }

        }

        MemoryWatcher::MemoryWatcher(const MemoryWatcher& c) {

            *this = c;

        }


        /////////////////////////////////////// using the user count ///////////////////////////////////////////////////

        void MemoryWatcher::createNewUserCount() {
            /** reserves a new user count & updates m_id
            * should be called when the data to be watched over is initialized or chaged
            * when there was old data stored in the object it should also be checked if this data
            * has any users left */



            m_user_id = s_user_count.size();
            s_user_count.push_back(1);


            //std::cout << "created user count" << m_user_id << "\n";
        }


        int MemoryWatcher::deleteUser() {
            /** deletes the user & returns the number of users left over
            * if no user (return: 0) is left, the data should be deleted */

            if(m_user_id == -1) {
                // the data was not initialized
                // so it should not get deleted
                return 1;
            }

            if(s_user_count.size() > (unsigned int) m_user_id) {
                s_user_count.at(m_user_id) -= 1;
            } else {
                std::cout << "failed to delete user " << m_user_id << "\n";
                std::cout << "user count does not exist " << "\n";
            }

            int old_user_id = m_user_id;
            m_user_id = -1; // object is deleted

            return s_user_count.at(old_user_id);
        }


    } // core

} // undicht
