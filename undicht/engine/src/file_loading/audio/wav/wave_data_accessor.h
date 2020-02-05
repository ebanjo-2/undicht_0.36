#ifndef WAVE_DATA_ACCESSOR_H
#define WAVE_DATA_ACCESSOR_H

#include <file_loading/RIFF/riff_sub_chunk_accessor.h>

namespace undicht {

    namespace audio {


        class WaveDataAccessor : public RiffSubChunkAccessor {
        public:

            char* getSamples();
            unsigned int getSize(); // the size of the sample data

            WaveDataAccessor();
            virtual ~WaveDataAccessor();


        };

    } // audio

} // undicht

#endif // WAVE_DATA_ACCESSOR_H
