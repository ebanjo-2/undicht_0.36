#include "riff_sub_chunk.h"


namespace undicht {

    namespace audio {

        RiffSubChunk::RiffSubChunk() {
            //ctor
        }


        RiffSubChunk::RiffSubChunk(const char* data) {
            /** initializes the chunk with the data found at the pointer
            * data should have at least 32 bytes associated (?) with it (you know what i mean) */

            setData(data);

        }

        RiffSubChunk::~RiffSubChunk() {
            //dtor
        }

        void RiffSubChunk::setData(const char* data){
                    /** initializes the chunk with the data found at the pointer
            * data should have at least 32 bytes associated (?) with it (you know what i mean) */

            m_id = *(int*)data;
            m_size = (*(int*)(data + 4)) + 8; // for some reason the size and id are excluded from the size in the file


            m_data = std::vector<char>(data + 8, data + m_size); // should store the data in the vector

        }


    } // audio

} // undicht
