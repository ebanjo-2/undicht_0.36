#ifndef RIFF_CHUNK_H
#define RIFF_CHUNK_H

#include "riff_sub_chunk.h"
#include <vector>


namespace undicht {

    namespace audio {


        class RiffChunk {

            public:
                // data (header of a riff file)

                int m_id = 0; // Contains the name of the chunk in ASCII form (i.e. "RIFF")
                int m_size = 0; // the files size in bytes (including the SubChunks)
                int m_format = 0; // contains closer information about the chunk (i.e. "WAVE")

                // thats were the actual data is stored
                std::vector<RiffSubChunk> m_sub_chunks;

            public:

                /** initializes the chunk with the data found at the pointer
                * data should have at least 32 bytes associated (?) with it (you know what i mean) */
                void setData(const char* data);

                RiffChunk();
                /** initializes the chunk with the data found at the pointer
                * data should have at least 32 bytes associated (?) with it (you know what i mean) */
                RiffChunk(const char* data);
                virtual ~RiffChunk();



        };


    } // audio

} // undicht


#endif // RIFF_CHUNK_H
