#include "riff_file_reader.h"
#include <iostream>

namespace undicht {

    namespace audio {

        RiffFileReader::RiffFileReader() {
            //ctor
        }

        RiffFileReader::~RiffFileReader() {
            //dtor
        }

        void RiffFileReader::open(std::string file_name) {

            ((FileReader*)this)->open(file_name);

            // reading the data into the main_chunk
            std::string data_buffer;
            m_main_chunk = RiffChunk(getAll(data_buffer).data());

        }


        void RiffFileReader::close() {

            m_main_chunk = RiffChunk();
            m_reader.close();

        }

    } // audio

} // undicht
