#ifndef DEV_TOOLS_H
#define DEV_TOOLS_H

#include <string>
#include <fstream>

namespace undicht {

    /** static functions that can speed up the creation of new code for the undicht 0.3 engine
    * for example */
    class DevTools {

    public:

        /** creates a .h and .cpp file for a new class that should be part of the undicht core
        * in its constructor it will load an object from the right shared lib (determined by the namespace the class is in)
        * which will be destroyed in its destructor
        * this mechanic is inherited from the SharedLibClass
        * @param file_path should end with an / */
        static void createCoreClass(const std::string& file_path, const std::string& class_name, const std::string& decl_namespace);

        static void createCoreImplClass(const std::string& file_path, const std::string& class_name, const std::string& decl_namespace, const std::string& impl_namespace);

    private:

        /** a function that returns a undicht style file name with all lowercase letters
        * and _ between two words based on the class_name given
        * (i.e. VertexBuffer would lead to vertex_buffer) */
        static std::string createFileName(const std::string& class_name);

        // returns whether c is a lower case letter
        static bool isLowerCase(char c);

        // returns whether c is a lower case letter
        static bool isUpperCase(char c);

        // makes c into a lower case letter
        static char makeLowerCase(char c);

        // makes c into an upper case letter
        static char makeUpperCase(char c);

        // adds a namespace around the strings content
        static void setNamespace(const std::string& namespace_name, std::string& file);

    };

} // undicht

#endif // DEV_TOOLS_H
