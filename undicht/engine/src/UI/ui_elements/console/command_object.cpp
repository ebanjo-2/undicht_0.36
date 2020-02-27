#include "command_object.h"


namespace undicht {

    CommandObject::CommandObject() {
        //ctor
    }

    CommandObject::CommandObject(const std::string& name) {

        setName(name);
    }

    CommandObject::~CommandObject() {
        //dtor
    }


    void CommandObject::onCall(const std::string& params) {
        /** gets called when the object was adressed in a command */


    }

    void CommandObject::setName(const std::string& name) {

        m_name = name;
    }

} // undicht
