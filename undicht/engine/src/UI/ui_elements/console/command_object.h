#ifndef COMMAND_OBJECT_H
#define COMMAND_OBJECT_H

#include <string>


namespace undicht {


    class CommandObject {
            /** @brief the parent object to all objects that want to receive commands from a console */

        public:

            /** gets called when the object was adressed in a command */
            virtual void onCall(const std::string& params);

        public:

            std::string m_name;

            virtual void setName(const std::string& name);


            CommandObject();
            CommandObject(const std::string& name);

            virtual ~CommandObject();

    };


} // undicht

#endif // COMMAND_OBJECT_H
