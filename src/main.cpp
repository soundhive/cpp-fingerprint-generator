#include <iostream>

#include <static_wav_decoder.hpp>

#include <fingerprint.h>

namespace wd = wav_decoder;

namespace fp = fingerprint;

int main(int argc, char const *argv[])
{
    std::shared_ptr<wd::audio_data> data = wd::decode("TEMP/test.wav");

    if (!data->is_valid)
    {
        return -1;
    }

    std::cout << data->audio_format << std::endl;
    std::cout << data->nb_channels << std::endl;
    std::cout << data->byte_rate << std::endl;
    std::cout << data->sample_rate << std::endl;
    std::cout << data->block_align << std::endl;
    std::cout << data->bits_per_sample << std::endl;
    std::cout << data->buffer_length << std::endl;


    short speech;
    
    float* num_data = new float[data->buffer_length / 2];
    
    std::ifstream f_in("TEMP/output.pcm", std::ios::in | std::ios::binary);
    int i = 0;
    while (true)
    {
        f_in.read((char *)&speech, 2);
        if (!f_in.good())
        {
            break;
        }
        num_data[i] = speech;
        i++;
    }
    f_in.close();

    std::string json = fp::fingerprint(num_data, i, data->sample_rate);
    delete[] num_data;
    std::ofstream json_prints;

    json_prints.open("TEMP/prints.txt", std::ios::out);
    json_prints << json;
    json_prints.close();

    // // Open output file
    // std::ofstream out_stream("TEMP/output.pcm", std::ofstream::binary);

    // // Check that the output stream is valid
    // if (!out_stream.good())
    // {
    //     std::cout << "Output stream to file "
    //               << "TEMP/output.pcm"
    //               << " is not valid" << std::endl;
    //     return -1;
    // }

    // out_stream.write(data->audio_buffer.get(), data->buffer_length);

    // out_stream.close();

    // std::cout << "- Copy done" << std::endl;
    return 0;
}
