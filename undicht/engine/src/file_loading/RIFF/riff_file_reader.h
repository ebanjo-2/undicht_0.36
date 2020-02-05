#ifndef RIFF_FILE_READER_H
#define RIFF_FILE_READER_H

#include <file_loading/file_reader.h>
#include "riff_chunk.h"


namespace undicht {

    namespace audio {


        class RiffFileReader : public FileReader {
                /** a class that holds the data of a RIFF formated file
                * RIFF is a specification for the storage of multimedia files
                * used by Microsoft in formats such as .wav
                * a File following RIFF consists of (a) main Chunk(s) and (a) SubChunk(s) */
                // source: http://soundfile.sapp.org/doc/WaveFormat/

            public:
                // storing the data in a more readeable form

                // contains the header data
                // and sub-chunks, where the actual data is stored
                RiffChunk m_main_chunk;

            public:
                // constr / destr

                void open(std::string file_name);

                virtual void close();


                RiffFileReader();
                virtual ~RiffFileReader();


        };


    } // audio

} // undicht

#endif // RIFF_FILE_READER_H
