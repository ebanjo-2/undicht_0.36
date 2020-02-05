#include "wave_file_reader.h"
#include <iostream>

namespace undicht {

    namespace audio {

        WaveFileReader::WaveFileReader() {
            //ctor
        }

        WaveFileReader::~WaveFileReader() {
            //dtor
        }

        void WaveFileReader::open(std::string file_name){

            ((RiffFileReader*)this)->open(file_name);

            // setting the data accessors
            char fmt[] = "fmt ";
            char data[] = "data";

            for(RiffSubChunk& rsc : m_main_chunk.m_sub_chunks){
                if(rsc.m_id == *(int*)fmt){
                    m_format.setDataSource(rsc);
                } else if(rsc.m_id == *(int*)data){
                    m_data.setDataSource(rsc);
                }
            }


        }

    } // audio

} // undicht
