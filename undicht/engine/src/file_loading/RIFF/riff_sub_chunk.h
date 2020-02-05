#ifndef RIFF_SUB_CHUNK_H
#define RIFF_SUB_CHUNK_H

#include <vector>

namespace undicht {

    namespace audio {


        class RiffSubChunk {

            public:
                // data

                int m_id = 0; // Contains the name of the chunk in ASCII form (i.e. "RIFF")
                int m_size = 0; // the files size in bits (including the SubChunks)


                std::vector<char> m_data;

            public:

                /** initializes the chunk with the data found at the pointer
                * data should have at least 32 bytes associated (?) with it (you know what i mean) */
                void setData(const char* data);

                RiffSubChunk();
                /** initializes the chunk with the data found at the pointer
                * data should have at least 32 bytes associated (?) with it (you know what i mean) */
                RiffSubChunk(const char* data);
                virtual ~RiffSubChunk();

        };


    } // audio

} // undicht

#endif // RIFF_SUB_CHUNK_H
