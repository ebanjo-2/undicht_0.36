#ifndef SOUND_SOURCE_H
#define SOUND_SOURCE_H

#include <core/shared_lib_class.h>
namespace undicht {

    namespace audio {

        SHARED_LIB_DECL_BASE_CLASS(SoundSource, SoundSourceBase, createSoundSource, copySoundSource, deleteSoundSource);

        SHARED_LIB_CLASS(class SoundSource: public SoundSourceBase{

            public:

                virtual void setData(const char* data, int byte_size, int format, int sample_rate);

                /** stores the data in the references
                * @param byte_size is the size of the data in bytes
                * @param format: the UND_AUDIO format (see core/types.h) */
                virtual const char* getData(int& byte_size, int& format, int& sample_rate);

                virtual void play();

                SoundSource();
                virtual ~SoundSource();

        };)

    } // audio

} // undicht


#endif // SOUND_SOURCE_H
