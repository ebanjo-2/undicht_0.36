#include "sound_file_reader.h"
#include <core/types.h>

using namespace undicht::core;

namespace undicht {

    namespace audio {


        SoundFileReader::SoundFileReader() {

        }


        SoundFileReader::~SoundFileReader() {

        }

        void SoundFileReader::open(std::string file_name) {

            m_file_name = file_name;

            if(hasFileType(file_name, ".wav")){
                m_wav_reader.open(file_name);
            }

        }

        void SoundFileReader::close() {

            m_wav_reader.close();

        }


        void SoundFileReader::loadSoundSource(SoundSource& loadTo) {

            if(hasFileType(m_file_name, ".wav")){


                loadTo.setData(m_wav_reader.m_data.getSamples(),
                 m_wav_reader.m_data.getSize(),
                 getAudioFormat(m_wav_reader.m_format.getNumChannels(), m_wav_reader.m_format.getBitsPerSample()),
                 m_wav_reader.m_format.getSampleRate());

            }

        }

        int SoundFileReader::getAudioFormat(int num_channels, int bits_per_sample){

            if(num_channels == 1){
                if(bits_per_sample == 8){
                    return UND_AUDIO_MONO8;
                } else if ( bits_per_sample == 16) {
                    return UND_AUDIO_MONO16;
                }
            } else if(num_channels == 2){
                if(bits_per_sample == 8){
                    return UND_AUDIO_STEREO8;
                } else if ( bits_per_sample == 16) {
                    return UND_AUDIO_STEREO16;
                }
            }

            return 0;
        }



    } // audio

} // undicht
