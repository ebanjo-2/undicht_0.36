#ifndef OPENAL_AUDIO_LIB_H
#define OPENAL_AUDIO_LIB_H

#include <audio/audio_lib.h>

namespace undicht {

    namespace audio {

        namespace openal {

            class AudioLib : public implementation::AudioLib {

                public:

                    static void initialize();

                    static void terminate();

                    // prints all available audio devices into the EventStack
                    static void listDevices();

            };

        } // openal

    } // audio

} // undicht


#endif // OPENAL_AUDIO_LIB_H
