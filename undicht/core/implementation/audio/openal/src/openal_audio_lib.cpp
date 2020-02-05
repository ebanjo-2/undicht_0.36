#include "openal_audio_lib.h"
#include <core/shared_lib.h>
#include <iostream>
#include <core/event_logger.h>

// this file was basically all taken from undicht 0.2...

#include <al.h>
#include <alc.h>
#include <cstring>

using namespace undicht::core;

namespace undicht {

    namespace audio {

        namespace openal {


            // global openal object pointers
            ALCdevice* g_device = 0;
            ALCcontext* g_context = 0;

            void AudioLib::initialize() {

                listDevices();

                g_device = alcOpenDevice(0);

                if(!g_device) {
                    EventLogger::storeNote(Note(UND_ERROR, "OPENAL:ERROR: failed to create audio device", UND_CODE_ORIGIN));
                }

                g_context = alcCreateContext(g_device, 0);
                alcMakeContextCurrent(g_context);

            }

            void AudioLib::terminate() {
                alcDestroyContext(g_context);
                alcCloseDevice(g_device);
            }

            void AudioLib::listDevices() {
                // source: https://ffainelli.github.io/openal-example/
                bool enumeration;

                enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

                if (enumeration == AL_FALSE) {
                    EventLogger::storeNote(Note(UND_WARNING, "OPENAL: failed to list audio devices", UND_CODE_ORIGIN));
                } else {
                    const char* devices = alcGetString(0, ALC_DEVICE_SPECIFIER);

                    const ALCchar *device = devices, *next = devices + 1;
                    size_t len = 0;

                    while (device && *device != '\0' && next && *next != '\0') {
                        EventLogger::storeNote(Note(UND_MESSAGE, std::string("found OPENAL audio device: ") + device, UND_CODE_ORIGIN));
                        len = strlen(device);
                        device += (len + 1);
                        next += (len + 2);
                    }

                }

            }

            /////////////////////// functions that can be accessed from outside the shared lib //////////

            SHARED_LIB_EXPORT void initialize() {

                AudioLib::initialize();

            }

            SHARED_LIB_EXPORT void terminate() {
                AudioLib::terminate();
            }


        } // openal

    } // audio

} // undicht
