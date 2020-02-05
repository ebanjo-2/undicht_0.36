#include "riff_sub_chunk_accessor.h"

namespace undicht {

    namespace audio {

        RiffSubChunkAccessor::RiffSubChunkAccessor() {
            //ctor
        }

        RiffSubChunkAccessor::~RiffSubChunkAccessor() {
            //dtor
        }

        void RiffSubChunkAccessor::setDataSource(RiffSubChunk& src){

            m_data_src = & src;

        }
    } // audio

} // undicht
