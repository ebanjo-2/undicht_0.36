#include <audio/sound_source.h>
namespace undicht {

    namespace audio {

        SHARED_LIB_DEF_BASE_CLASS( SoundSource, createSoundSource, copySoundSource, deleteSoundSource);

        SHARED_LIB_API_IMPL(SoundSource::SoundSource()){

        }

        SHARED_LIB_API_IMPL(SoundSource::~SoundSource()){

        }

        SHARED_LIB_API_IMPL(void SoundSource::setData(const char* data, int byte_size, int format, int sample_rate)){

            m_shared_lib_object->setData(data, byte_size, format, sample_rate);
        }


        SHARED_LIB_API_IMPL(const char* SoundSource::getData(int& byte_size, int& format, int& sample_rate)){

            return m_shared_lib_object->getData( byte_size, format, sample_rate);
        }



        SHARED_LIB_API_IMPL(void SoundSource::play()){

            m_shared_lib_object->play();
        }


    } // audio

} // undicht
