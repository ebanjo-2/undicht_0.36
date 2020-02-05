#include "shared_id.h"

namespace undicht {

    namespace core {

        SharedID::SharedID() {
            //ctor
        }

        SharedID::SharedID(unsigned int id){

            setID(id);

        }

        SharedID::~SharedID() {
            //dtor
        }


        void SharedID::setID(unsigned int id){

            // removeUser should be called separately to delete the id object
            createNewUserCount();
            m_id = id;

        }

        unsigned int& SharedID::getID(){

            return m_id;
        }


        bool SharedID::removeUser(){
            /** to be called when an object referencing the id is destroyed
            * @return true when the object being destroyed is the last one referencing the id */

            return !deleteUser();
        }

        void SharedID::operator= (unsigned int id){

            setID(id);
        }

        SharedID::operator unsigned int(){

            return m_id;
        }

    } // core

} // undicht
