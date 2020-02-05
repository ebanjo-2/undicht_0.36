#ifndef AUDIO_LIB_H
#define AUDIO_LIB_H

#include <core/shared_lib_class.h>

namespace undicht {

    namespace audio {

        SHARED_LIB_CLASS(class AudioLib {
            public:

                static void initialize();

                static void terminate();

                AudioLib();
                virtual ~AudioLib();


        };)

    } // audio

} // undicht


#endif // AUDIO_LIB_H
