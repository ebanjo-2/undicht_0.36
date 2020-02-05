#include <audio/audio_lib.h>
#include <core/core.h>

#include <audio/sound_source.h>


namespace undicht {

    namespace audio {

        void AudioLib::initialize() {

            ((void(*)())core::Core::s_audio_lib.getFunction("initialize")) ();

            // initializing the functions to load audio objects from the shared lib
            createSoundSource = (implementation::SoundSource*(*)())core::Core::s_audio_lib.getFunction("createSoundSource");
            copySoundSource = (void(*)(implementation::SoundSource*,implementation::SoundSource*))core::Core::s_audio_lib.getFunction("copySoundSource");
            deleteSoundSource = (void(*)(implementation::SoundSource*))core::Core::s_audio_lib.getFunction("deleteSoundSource");

        }

        void AudioLib::terminate(){

              ((void(*)())core::Core::s_audio_lib.getFunction("terminate")) ();

        }

    } // audio

} // undicht
