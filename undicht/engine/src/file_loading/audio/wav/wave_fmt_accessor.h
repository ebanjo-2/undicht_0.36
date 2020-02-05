#ifndef WAVE_FMT_ACCESSOR_H
#define WAVE_FMT_ACCESSOR_H

#include <file_loading/RIFF/riff_sub_chunk_accessor.h>


namespace undicht {

    namespace audio {


        class WaveFmtAccessor : public RiffSubChunkAccessor {
            /** a  class that makes the data of the fmt wave subchunk easier to access */
        public:

            // comments adopted from source:
            // http://soundfile.sapp.org/doc/WaveFormat/ (07.07.2019)
            unsigned short getAudioFormat(); // should be 1
            unsigned short getNumChannels(); // 1 = Mono, 2 = Stereo, ...
            unsigned int getSampleRate(); //
            unsigned int getByteRate(); // == SampleRate * NumChannels * BitsPerSample/8
            unsigned short getBlockAlign(); // == NumChannels * BitsPerSample/8
                                   // The number of bytes for one sample including
                                   // all channels.
            unsigned short getBitsPerSample(); // does what it says


            WaveFmtAccessor();
            virtual ~WaveFmtAccessor();

        };

    } // audio

} // undicht

#endif // WAVE_FMT_ACCESSOR_H
