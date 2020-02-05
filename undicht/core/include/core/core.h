#ifndef CORE_H
#define CORE_H

#include <core/shared_lib.h>
#include <string>

#include <chrono>
#include <ctime>


namespace undicht {

    namespace core {


        class Core {

            public:
                // the shared libraries used to load the platform specific core functions

                static SharedLib s_window_lib;
                static SharedLib s_video_lib;
                static SharedLib s_audio_lib;


                static std::string s_window_lib_path;
                static std::string s_video_lib_path;
                static std::string s_audio_lib_path;

                static std::chrono::high_resolution_clock::time_point s_startup_time;


            public:

                // tells the core which libraries it should initialize with
                static void setLibraryPaths(const std::string& window, const std::string& video, const std::string& audio);

                // initializes the shared libraries
                static void initialize();

                // closes shared libraries
                static void terminate();

            public:

                /** @return the time in seconds since the core was initialized */
                static double getTime();


        };


    } // core

} // undicht

#endif // CORE_H
