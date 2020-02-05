#include "core.h"
#include <iostream>
#include <core/event_logger.h>
#include <window/window.h>
#include <window/graphics_context.h>

using namespace std::chrono;

namespace undicht {

    namespace core {

#ifdef UND_UNIX
    // for linux
    std::string Core::s_window_lib_path = "../undicht/core/implementation/window/glfw/libwindow_glfw.so";
    std::string Core::s_video_lib_path = "../undicht/core/implementation/graphics/opengl_33/libvideo_opengl_33.so";
    std::string Core::s_audio_lib_path = "../undicht/core/implementation/audio/openal/libaudio_openal.so";
#endif // UND_UNIX


#ifdef UND_WINDOWS
    // for windows
    std::string Core::s_window_lib_path = "../undicht/core/implementation/window/glfw/window_glfw.dll";
    std::string Core::s_video_lib_path = "../undicht/core/implementation/graphics/opengl_33/video_opengl_33.dll";
    std::string Core::s_audio_lib_path = "../undicht/core/implementation/audio/openal/audio_openal.dll";
#endif // UND_UNIX


        SharedLib Core::s_window_lib;
        SharedLib Core::s_video_lib;
        SharedLib Core::s_audio_lib;

        high_resolution_clock::time_point Core::s_startup_time;

        void Core::setLibraryPaths(const std::string& window, const std::string& video, const std::string& audio){

            s_window_lib_path = window;
            s_video_lib_path = video;
            s_audio_lib_path = audio;


        }

        // loads shared libraries
        void Core::initialize() {

            s_startup_time = high_resolution_clock::now();


            // setting some static event messages
            Note::setStaticMessage("EVENT: MESSAGE: EMPTY MESSAGE", 0);
            Note::setStaticMessage("DLL ERROR 126", 126);
            Note::setStaticMessage("DLL ERROR 127 (failed to find procedure)", 127);

            s_window_lib.open(s_window_lib_path);
            s_video_lib.open(s_video_lib_path);
            s_audio_lib.open(s_audio_lib_path);


        }

        // closes shared libraries
        void Core::terminate() {
            s_window_lib.close();
            s_video_lib.close();
            s_audio_lib.close();
        }

        double Core::getTime() {

            high_resolution_clock::time_point now = high_resolution_clock::now();

            duration<double> time_since_startup = duration_cast<duration<double>>(now - s_startup_time);

            return time_since_startup.count();
        }

    } // core

} // undicht

