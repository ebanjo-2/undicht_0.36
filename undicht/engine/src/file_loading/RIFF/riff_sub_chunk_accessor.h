#ifndef RIFF_SUB_CHUNK_ACCESSOR_H
#define RIFF_SUB_CHUNK_ACCESSOR_H


#include <file_loading/RIFF/riff_sub_chunk.h>


namespace undicht {

    namespace audio {


        class RiffSubChunkAccessor {
            /** the base class to classes that provide an easier access to the data of a
            * Riff sub chunk */
        public:

            RiffSubChunk* m_data_src = 0;

            void setDataSource(RiffSubChunk& src);


            RiffSubChunkAccessor();
            virtual ~RiffSubChunkAccessor();

        };

    } // audio

} // undicht

#endif // RIFF_SUB_CHUNK_ACCESSOR_H
