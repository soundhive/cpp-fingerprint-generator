#include <iostream>

#include <static_wav_decoder.hpp>

#include <fingerprint.h>

#define MINIMP3_FLOAT_OUTPUT
#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

#define OPTIMIZED_BUFFER_SIZE 16 384;

namespace wd = wav_decoder;

namespace fp = fingerprint;

namespace fs = std::experimental::filesystem;

void save_audio_pcm(float *buffer, size_t length, std::string &file_name)
{
    // Open output file
    std::ofstream out_stream("TEMP/" + file_name, std::ofstream::binary);

    // Check that the output stream is valid
    if (!out_stream.good())
    {
        std::cout << "Output stream to file "
                  << "TEMP/" << file_name
                  << " is not valid" << std::endl;
        return;
    }

    out_stream.write(reinterpret_cast<char *>(buffer), length);

    out_stream.close();


}

std::shared_ptr<wd::audio_data> run_wav_decoder()
{
    std::cout << "running wav decoder." << std::endl;

    std::shared_ptr<wd::audio_data> data = wd::decode("TEMP/test.wav");

    std::cout << "format : " << data->audio_format << std::endl;
    std::cout << "channels : " << data->nb_channels << std::endl;
    std::cout << "byte rate : " << data->byte_rate << std::endl;
    std::cout << "sample rate : " << data->sample_rate << std::endl;
    std::cout << "block align : " << data->block_align << std::endl;
    std::cout << "bits per sample : " << data->bits_per_sample << std::endl;
    std::cout << "buffer length : " << data->buffer_length << std::endl;

    std::string out_file("wav_file.pcm");

     for (int i = 1000000; i < 1000020; i++) {
        std::cout << data->audio_buffer.get()[i] << std::endl;
    }

    save_audio_pcm(data->audio_buffer.get(), data->buffer_length, out_file);
    return data;
}

void run_fingerprint_generator(float *buffer, size_t buffer_size, int sample_rate)
{
    

    std::string json = fp::fingerprint(buffer, buffer_size, sample_rate);

    std::ofstream json_prints;

    json_prints.open("TEMP/prints.txt", std::ios::out);
    json_prints << json;
    json_prints.close();
}

void run_mp3_decoder()
{
    std::cout << "running mp3 decoder." << std::endl;

    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, "TEMP/test.mp3", &info, NULL, NULL))
    {
        std::cout << "an error occured decoding the file.";
    }
    /* mp3dec_file_info_t contains decoded samples and info,
       use free(info.buffer) to deallocate samples */



    std::cout << "samples : " << info.samples << std::endl;
    std::cout << "hz : " << info.hz << std::endl;
    std::cout << "buffer : " << info.buffer << std::endl;

    std::string out_file("mp3_file.pcm");

    save_audio_pcm(info.buffer, info.samples * sizeof(mp3d_sample_t), out_file);

    std::cout << "saved file" << std::endl;
    
}

int main(int argc, char const *argv[])
{
    run_wav_decoder();
    //run_mp3_decoder();

    

    //auto data = run_wav_decoder();

    //run_fingerprint_generator(data);

    return 0;
}
// short speech;
    // size_t size = fs::file_size("TEMP/output.pcm");
    // float *num_data = new float[size / 2];

    // std::ifstream f_in("TEMP/output.pcm", std::ios::in | std::ios::binary);
    // int i = 0;
    // while (f_in.good())
    // {
    //     f_in.read((char *)&speech, 2);
    //     num_data[i] = speech;
    //     i++;
    // }
    // f_in.close();