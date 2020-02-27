#ifndef CONSOLE_H
#define CONSOLE_H

#include "command_object.h"

namespace undicht {

    class Console {
            /** @brief a console that uses the undicht ui
            * it should support custom, user defined commands */

        public:
            // adding (custom) commands to the console

            /** adds the command object into the list of command object usable from the console
            * @return true if the command object has a unique name (if not, the command will not be added)*/
            bool addCommand();


            Console();
            virtual ~Console();

    };


} // undicht

#endif // CONSOLE_H
