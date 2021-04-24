#include <iostream>
#include <fstream>

#include <mp3_handler.hpp>
#include <wav_handler.hpp>



namespace fs = std::experimental::filesystem;




int main(int argc, char const *argv[])
{

    if (!argv[1] || !argv[2])
    {

        std::cerr << "You must specify an input file and then an output file." << std::endl;
        exit(-1);
    }
    std::string in_path = argv[1];
    std::string out_path = argv[2];

    std::string extension(in_path.substr(in_path.length() - 4, in_path.length() - 1));
    std::cout << extension << std::endl;

    if (extension == ".mp3")
    {

        std::string mp3_in_f = run_mp3_decoder(in_path);

        std::cout << "Writing the prints out of PCM in :" << mp3_in_f << std::endl;
        

        // fingerprint_from_pcm(mp3_in_f, out_path, mp3_infos.hz);
        

    }
    else if (extension == ".wav")
    {

        std::string wav_infos = run_wav_decoder(in_path);
        std::string wav_in_f("raw_audio.pcm");

        // fingerprint_from_pcm(wav_in_f, out_path, wav_infos->sample_rate);
    }

    return 0;
}
