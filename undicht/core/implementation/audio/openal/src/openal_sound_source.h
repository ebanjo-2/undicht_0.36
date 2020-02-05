#ifndef OPENAL_SOUND_SOURCE_H
#define OPENAL_SOUND_SOURCE_H

#include <audio/sound_source.h>

namespace undicht {

    namespace audio {

        namespace openal {

            class SoundSource : public implementation::SoundSource {

                public:

                    // the id of the openal sound buffer
                    unsigned int m_buffer_id = 0;
                    unsigned int m_speaker_id = 0;

                    // data defining the sound played
                    char* m_data = 0; // since i havent found a way to get the data back from the buffer, it has to be store twice
                    int m_size = 0;
                    int m_undicht_format = 0;
                    int m_sample_rate = 0;

                    virtual void setData(const char* data, int byte_size, int format, int sample_rate);
                    virtual const char* getData(int& byte_size, int& format, int& sample_rate);

                    virtual void play();

                    // converts the undicht audio format type into an openal one
                    int getOpenalFormat(int und_format);

                    SoundSource();
                    virtual ~SoundSource();

            };

        } // openal

    } // audio

} // undicht


#endif // OPENAL_SOUND_SOURCE_H
