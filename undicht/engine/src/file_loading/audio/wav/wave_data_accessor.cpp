#include "wave_data_accessor.h"

namespace undicht {

    namespace audio {

        WaveDataAccessor::WaveDataAccessor() {
            //ctor
        }

        WaveDataAccessor::~WaveDataAccessor() {
            //dtor
        }

        char* WaveDataAccessor::getSamples(){

            return m_data_src->m_data.data();
        }

        unsigned int WaveDataAccessor::getSize() {

            return m_data_src->m_data.size();
        }

    } // audio

} // undicht
