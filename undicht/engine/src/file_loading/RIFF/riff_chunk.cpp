#include "riff_chunk.h"
#include <iostream>
#include <core/event_logger.h>

using namespace undicht::core;

namespace undicht {

    namespace audio {


        RiffChunk::RiffChunk() {
            //ctor
        }


        RiffChunk::RiffChunk(const char* data) {
            /** initializes the chunk with the data found at the pointer
            * data should have at least 32 bytes associated (?) with it (you know what i mean) */

            setData(data);

        }


        RiffChunk::~RiffChunk() {
            //dtor
        }

        void RiffChunk::setData(const char* data){
            /** initializes the chunk with the data found at the pointer
            * data should have at least 32 bytes associated (?) with it (you know what i mean) */

            m_id = *(int*)data;
            m_size = (*(int*)(data + 4)) + 8; // the size in the header does not include the first 8 bytes
            m_format = *(int*)(data + 8);

            for(int sub_chunk_start = 12; sub_chunk_start < m_size; sub_chunk_start += m_sub_chunks.back().m_size){

                m_sub_chunks.emplace_back(RiffSubChunk(data + sub_chunk_start));

                if(sub_chunk_start + m_sub_chunks.back().m_size > m_size){

                    EventLogger::storeNote(Note(UND_ERROR, "stop right there! you violated the law \n (ERROR: Riff chunk exceeded the file size)", UND_CODE_ORIGIN));

                }

            }

        }


    } // audio

} // undicht
