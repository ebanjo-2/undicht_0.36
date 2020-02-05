#include "wave_fmt_accessor.h"

namespace undicht {

    namespace audio {

        WaveFmtAccessor::WaveFmtAccessor() {
            //ctor
        }

        WaveFmtAccessor::~WaveFmtAccessor() {
            //dtor
        }

        unsigned short WaveFmtAccessor::getAudioFormat(){
            // should be 1
            return *(unsigned short*)(m_data_src->m_data.data() + 0);
        }

        unsigned short WaveFmtAccessor::getNumChannels() {
            // 1 = Mono, 2 = Stereo, ...
            return *(unsigned short*)(m_data_src->m_data.data() + 2);
        }

        unsigned int WaveFmtAccessor::getSampleRate() {

            return *(unsigned int*)(m_data_src->m_data.data() + 4);
        }


        unsigned int WaveFmtAccessor::getByteRate(){
            // == SampleRate * NumChannels * BitsPerSample/8

            return *(unsigned int*)(m_data_src->m_data.data() + 8);
        }

        unsigned short WaveFmtAccessor::getBlockAlign(){
            // == NumChannels * BitsPerSample/8
            // The number of bytes for one sample including
            // all channels.

            return *(unsigned short*)(m_data_src->m_data.data() + 12);
        }

        unsigned short WaveFmtAccessor::getBitsPerSample(){
            // does what it says

            return *(unsigned short*)(m_data_src->m_data.data() + 14);
        }


    } // audio

} // undicht
