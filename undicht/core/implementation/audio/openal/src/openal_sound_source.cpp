#include "openal_sound_source.h"
#include <al.h>
#include <alc.h>
#include <core/types.h>

using namespace undicht::core;

namespace undicht {

    namespace audio {

        namespace openal {

            SoundSource::SoundSource() {

                alGenBuffers(1, &m_buffer_id);

                alGenSources(1, &m_speaker_id);
                alSourcef(m_speaker_id, AL_GAIN, 1);
                alSourcef(m_speaker_id, AL_PITCH, 1);
                alSource3f(m_speaker_id, AL_POSITION, 0,0,0);
            }


            SoundSource::~SoundSource() {

                alDeleteBuffers(1, &m_buffer_id);
                m_buffer_id = 0;

                alDeleteSources(1, &m_speaker_id);
                m_speaker_id = 0;

                if(m_data) delete[] m_data;
            }

            void SoundSource::setData(const char* data, int byte_size, int format, int sample_rate) {

                m_size = byte_size;
                m_undicht_format = format;
                m_sample_rate = sample_rate;

                if(m_data) delete[] m_data;
                m_data = new char[byte_size];
                std::copy(data, data + byte_size, m_data);

                alBufferData(m_buffer_id, getOpenalFormat(format), data, byte_size, sample_rate);
            }

            const char* SoundSource::getData(int& byte_size, int& format, int& sample_rate) {

                byte_size = m_size;
                format = m_undicht_format;
                sample_rate = m_sample_rate;


                return m_data;
            }


            void SoundSource::play() {
                alSourcei(m_speaker_id, AL_BUFFER, m_buffer_id);
                alSourcePlay(m_speaker_id);
            }

            // converts the undicht audio format type into an openal one
            int SoundSource::getOpenalFormat(int und_format) {

                if(und_format == UND_AUDIO_MONO8) {
                    return AL_FORMAT_MONO8;
                } else if(und_format == UND_AUDIO_MONO16) {
                    return AL_FORMAT_MONO16;
                } else if(und_format == UND_AUDIO_STEREO8) {
                    return AL_FORMAT_STEREO8;
                } else if(und_format == UND_AUDIO_STEREO16) {
                    return AL_FORMAT_STEREO16;
                }

                return 0;
            }


            //////////////////// functions to load from the shared lib /////////

            SHARED_LIB_EXPORT implementation::SoundSource*createSoundSource() {
                return new openal::SoundSource;
            }

            SHARED_LIB_EXPORT void copySoundSource(implementation::SoundSource* c, implementation::SoundSource* o) {
                // copying the data from *o to *c
                int format, sample_rate, byte_size;
                const char* data = o->getData(byte_size, format, sample_rate);
                c->setData(data, byte_size, format, sample_rate);
            }

            SHARED_LIB_EXPORT void deleteSoundSource(implementation::SoundSource* object) {
                delete (SoundSource*)object;
            }


        } // openal

    } // audio

} // undicht
