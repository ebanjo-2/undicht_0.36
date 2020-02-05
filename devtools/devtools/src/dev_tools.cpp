#include "dev_tools.h"
#include <fstream>
#include <array>
#include <iostream>


namespace undicht {


    void DevTools::createCoreClass(const std::string& file_path, const std::string& class_name, const std::string& decl_namespace) {

        // get the name base of the files
        std::string file_name_base = createFileName(class_name);

        // create the source code for the header file
        std::string header_src;

        header_src.insert(0, "SHARED_LIB_CLASS(class " + class_name
                          + ": public " + class_name + "Base" + "{\n"
                          + "};)\n");


        header_src.insert(0, "SHARED_LIB_DECL_BASE_CLASS("
                          + class_name + ", " + class_name + "Base" + ", "
                          + "create" + class_name + ", "
                          + "copy" + class_name + ", "
                          + "delete" + class_name + ");" + "\n" + "\n");

        setNamespace(decl_namespace, header_src);
        setNamespace("undicht", header_src);
        header_src.insert(0,"#include <core/shared_lib_class.h>\n");

        // creating the header guard
        std::string header_guard;
        for(char& c : file_name_base) {
            header_guard.push_back(makeUpperCase(c));
        }
        header_guard += "_H";
        header_src.insert(0, "#ifndef " + header_guard + "\n"
                          + "#define " + header_guard + "\n\n");
        header_src.insert(header_src.size(), "\n\n#endif // " + header_guard);

        // create the source code for the source file
        std::string cpp_src;

        cpp_src.insert(0, "SHARED_LIB_DEF_BASE_CLASS( " + class_name
                       + ", create" + class_name + ", copy" + class_name + ", delete" + class_name
                       + ");\n");

        setNamespace(decl_namespace, cpp_src);
        setNamespace("undicht", cpp_src);

        cpp_src.insert(0, "#include <" + file_name_base + ".h>\n");



        // create the header file, deleting any previous content
        std::fstream h_file(file_path + file_name_base + ".h", std::fstream::trunc | std::fstream::out);
        h_file.write(header_src.data(), header_src.size());
        std::cout << "created " << file_path + file_name_base + ".h :" << "\n";
        std::cout << header_src << "\n" << "\n";


        // create the cpp file, deleting any previous content
        std::fstream cpp_file(file_path + file_name_base + ".cpp", std::fstream::trunc | std::fstream::out);
        cpp_file.write(cpp_src.data(), cpp_src.size());
        std::cout << "created " << file_path + file_name_base + ".cpp :" << "\n";
        std::cout << cpp_src << "\n" << "\n";

        // closing both files
        h_file.close();
        cpp_file.close();

    }


    void DevTools::createCoreImplClass(const std::string& file_path, const std::string& class_name, const std::string& decl_namespace, const std::string& impl_namespace) {
        // get the name base of the files

        std::string decl_file_name_base = createFileName(class_name);
        std::string file_name_base = impl_namespace + "_" + decl_file_name_base;

        // create the source code for the header file
        std::string header_src;

        header_src.insert(0, "class " + class_name
                          + " : public implementation::" + class_name + " {\n\n"
                          + "};\n");


        setNamespace(impl_namespace, header_src);
        setNamespace(decl_namespace, header_src);
        setNamespace("undicht", header_src);

        header_src.insert(0, "#include <" + decl_namespace + "/" + decl_file_name_base + ".h>\n\n");

        // creating the header guard
        std::string header_guard;
        for(char& c : file_name_base) {
            header_guard.push_back(makeUpperCase(c));
        }
        header_guard += "_H";
        header_src.insert(0, "#ifndef " + header_guard + "\n"
                          + "#define " + header_guard + "\n\n");
        header_src.insert(header_src.size(), "\n\n#endif // " + header_guard);

        // create the source code for the source file
        std::string cpp_src;

        // creating the functions to load an object from the shared lib

        cpp_src.insert(0, "SHARED_LIB_EXPORT void delete" + class_name
        + "(implementation::" + class_name + "* object){\n"
        + "delete (" + class_name + "*)object;\n}\n\n");

        cpp_src.insert(0, "SHARED_LIB_EXPORT void copy" + class_name
        + "(implementation::" + class_name + "* c, implementation::" + class_name + "* o){\n"
        + "*(" + class_name + "*)c = *(" + class_name + "*)o;\n}\n\n");

        cpp_src.insert(0, "SHARED_LIB_EXPORT implementation::" + class_name + "*"
        + "create" + class_name + "(){\n"
        + "return new " + impl_namespace + "::" + class_name + ";\n}\n\n");



        setNamespace(impl_namespace, cpp_src);
        setNamespace(decl_namespace, cpp_src);
        setNamespace("undicht", cpp_src);

        std::string empty_string; // needed, since the char " cant be added to the const char*
        cpp_src.insert(0, empty_string + "#include " + '"' + file_name_base + ".h" + '"' + "\n\n");



        // create the header file, deleting any previous content
        std::fstream h_file(file_path + file_name_base + ".h", std::fstream::trunc | std::fstream::out);
        h_file.write(header_src.data(), header_src.size());
        std::cout << "created " << file_path + file_name_base + ".h :" << "\n";
        std::cout << header_src << "\n" << "\n";


        // create the cpp file, deleting any previous content
        std::fstream cpp_file(file_path + file_name_base + ".cpp", std::fstream::trunc | std::fstream::out);
        cpp_file.write(cpp_src.data(), cpp_src.size());
        std::cout << "created " << file_path + file_name_base + ".cpp :" << "\n";
        std::cout << cpp_src << "\n" << "\n";

        // closing both files
        h_file.close();
        cpp_file.close();
    }

    /////////////////////////// private tools for the public tools ////////////

    std::string DevTools::createFileName(const std::string& class_name) {
        /** a function that returns a undicht style file name with all lowercase letters
        * and _ between two words based on the class_name given
        * (i.e. VertexBuffer would lead to vertex_buffer) */

        std::string file_name;
        size_t pos_in_class_name = 0;

        // going through the class name searching for individual words
        while(pos_in_class_name < class_name.size()) {

            // testing whether a new word is about to begin
            if(isUpperCase(class_name.at(pos_in_class_name))) {
                // adding a _ only if its not the beginning of the class_name
                if(pos_in_class_name) {
                    file_name.push_back('_');
                }
            }

            // making the next character a lower letter
            file_name.push_back(makeLowerCase(class_name.at(pos_in_class_name)));

            pos_in_class_name++;
        }

        return file_name;
    }

    bool DevTools::isLowerCase(char c) {
        // returns whether c is a lower case letter

        if((int)c >= (int)'a' && (int)c <= (int)'z') {
            return true;
        }

        return false;
    }

    bool DevTools::isUpperCase(char c) {
        // returns whether c is a lower case letter

        if((int)c >= (int)'A' && (int)c <= (int)'Z') {
            return true;
        }

        return false;
    }

    char DevTools::makeLowerCase(char c) {
        // makes c into a lower case letter

        if(isUpperCase(c)) {
            // this is how chars work?
            return (char)((int)c - ((int)'A' - (int)'a'));
        }

        return c; // either not a letter or already lower case
    }

    char DevTools::makeUpperCase(char c) {
        // makes c into an upper case letter

        if(isLowerCase(c)) {
            // this is how chars work?
            return (char)((int)c + ((int)'A' - (int)'a'));
        }

        return c; // either not a letter or already upper case
    }


    void DevTools::setNamespace(const std::string& namespace_name, std::string& file) {
        // adds a namespace around the strings content

        file.insert(0, "namespace " + namespace_name + " {" + "\n\n");
        file.insert(file.size(), "\n} // " + namespace_name + "\n");

    }


} // undicht
