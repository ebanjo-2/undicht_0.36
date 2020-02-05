#ifndef SHARED_LIB_H
#define SHARED_LIB_H

#include <string>
#include <iostream>

#include <core/note.h>


// different compilers use different functions to load dlls
// but the main EventLoggeric is pretty much the same

#if defined(unix) || defined(__unix__) || defined(__unix)
    // functions that should be imported from the lib should be marked with SHARED_LIB_EXPORT
    #define UND_UNIX
    #include <dlfcn.h>
    #define SHARED_LIB_EXPORT extern "C"
    #define SHARED_LIB_ERROR dlerror() // should return a char* (trying to create a string from a char null pointer crashed, this seems to work though ...)
    #define SHARED_LIB_TYPE void* // the object type used to reference the shared lib
    #define SHARED_LIB_OPEN(file_name) dlopen(file_name, RTLD_NOW|RTLD_GLOBAL) // the function that opens the lib, file name should be the file name as const char*
    #define SHARED_LIB_CLOSE(ref) dlclose(ref) // the function that closes the lib, ref is the referencing object to the lib
    #define SHARED_LIB_LOAD(ref,func_name) dlsym(ref, name.data()) // returns the function requested

#endif

#ifdef _WIN32 // probably mingw
    // functions that should be imported from the lib should be marked with SHARED_LIB_EXPORT
    #define UND_WINDOWS
    #include <windows.h>
    #define SHARED_LIB_EXPORT extern "C" __declspec(dllexport)
    #define SHARED_LIB_ERROR GetLastError() // should return an int
    #define SHARED_LIB_TYPE HINSTANCE  // the object type used to reference the shared lib
    #define SHARED_LIB_OPEN(file_name) LoadLibrary(file_name) // the function that opens the lib, file name should be the file name as const char*, returns the reference (ref) to the lib
    #define SHARED_LIB_CLOSE(ref) FreeLibrary(ref) // the function that closes the lib, ref is the referencing object to the lib
    #define SHARED_LIB_LOAD(ref,func_name) GetProcAddress(ref, func_name) // returns the function requested, func_name should be a const char*
#endif // defined


// duplicates the class declaration in the namespace implementation,
// which is the namespace in which the shared lib should implement the functions
// this way the class in the default namespace can be used to implement the api to access the implementation
// the default class will also have a public implementation::class_name pointer added to it
// to store the actual object loaded from the shared lib
#define SHARED_LIB_CLASS(class_decl)  class_decl \
    namespace implementation { class_decl }

// used to invisibly implement the implementation::class too
#define SHARED_LIB_API_IMPL(func_head) namespace implementation{func_head{}} func_head





namespace undicht {

    namespace core {

        class SharedLib {
                /** a class representing a shared library (i.e. .dll or .so)
                * and providing an interface to load functions from the library
                * if you want to load objects, use a function that creates one with new in the shared lib
                * and returns it (you should also use a function to delete it) */

            public:

                SharedLib();
                SharedLib(const std::string& file_name);
                virtual ~SharedLib();

                void open(const std::string& file_name);

                void close();

                /** returns a pointer to the requested function
                * the function should be exported with SHARED_LIB_EXPORT */
                void* getFunction(const std::string& name);

            protected:

                std::string m_file_name;
                SHARED_LIB_TYPE m_handle = 0;

        };

    } // core

} // undicht

#endif // SHARED_LIB_H
