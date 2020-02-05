#ifndef STRING_TOOLS_H_INCLUDED
#define STRING_TOOLS_H_INCLUDED

#include <sstream>

// some simple string tools

namespace undicht {

    namespace core {

        /** gives you a string containing data about
        * the location of the line this makro is used in
        * (file_path : line_number) */
        #define UND_CODE_ORIGIN undicht::core::toStr(__FILE__) + undicht::core::toStr(" : ") + undicht::core::toStr(__LINE__)

        #define UND_CODE_SRC_FILE undicht::core::toStr(__FILE__)

        /** tries to convert everything into a string */
        template <typename T>
        std::string toStr(const T& t){
            std::stringstream s;
            s << t;
            return s.str();
        }


    }

}



#endif // STRING_TOOLS_H_INCLUDED
