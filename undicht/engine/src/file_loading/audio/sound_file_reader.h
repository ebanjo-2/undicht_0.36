#ifndef SOUND_FILE_H
#define SOUND_FILE_H

#include <string>
#include <audio/sound_source.h>
#include <file_loading/audio/wav/wave_file_reader.h>



namespace undicht {

    namespace audio {
        /** a class to read all supported sound files */


        class SoundFileReader : public FileReader{
            public:

                // used to read .wav files
                WaveFileReader m_wav_reader;

                void open(std::string file_name);

                virtual void close();

                SoundFileReader();
                virtual ~SoundFileReader();

                static int getAudioFormat(int num_channels, int bits_per_sample);

                void loadSoundSource(SoundSource& loadTo);


        };

    } // audio

} // undicht

#endif // SOUND_FILE_H
