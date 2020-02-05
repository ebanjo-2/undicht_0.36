#ifndef WAVE_FILE_READER_H
#define WAVE_FILE_READER_H

#include <file_loading/RIFF/riff_file_reader.h>
#include "wave_fmt_accessor.h"
#include "wave_data_accessor.h"

namespace undicht {

    namespace audio {


        class WaveFileReader : public RiffFileReader {
        public:
            // fmt subchunk

            WaveFmtAccessor m_format;

        public:
            // data subchunk

            WaveDataAccessor m_data;

        public:
            // general functions

            virtual void open(std::string file_name);

            WaveFileReader();
            virtual ~WaveFileReader();


        };

    } // audio

} // undicht

#endif // WAVE_FILE_READER_H
