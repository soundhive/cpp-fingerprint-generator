#include <iostream>

#include <static_wav_decoder.hpp>

#include <fingerprint.h>

//#define MINIMP3_FLOAT_OUTPUT
#define MINIMP3_IMPLEMENTATION
#include <minimp3.h>
#include <minimp3_ex.h>

namespace wd = wav_decoder;

namespace fp = fingerprint;

namespace fs = std::experimental::filesystem;

void save_audio_wav_pcm(char *buffer, size_t length, std::string &file_name)
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

    out_stream.write(buffer, length);

    out_stream.close();

    std::cout << "- Copy done" << std::endl;
}

void save_audio_mp3_pcm(mp3d_sample_t *buffer, size_t length, std::string &file_name)
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

    std::string out_file("raw_audio.pcm");

    save_audio_wav_pcm(data->audio_buffer.get(), data->buffer_length, out_file);

    return data;
}

mp3dec_file_info_t run_mp3_decoder()
{
    std::cout << "running mp3 decoder." << std::endl;

    mp3dec_t mp3d;
    mp3dec_file_info_t info;
    if (mp3dec_load(&mp3d, "TEMP/test.mp3", &info, NULL, NULL))
    {
        std::cout << "an error occured decoding the file.";
        exit(-1);
    }
    /* mp3dec_file_info_t contains decoded samples and info,
       use free(info.buffer) to deallocate samples */

    std::cout << "samples : " << info.samples << std::endl;
    std::cout << "hz : " << info.hz << std::endl;
    std::cout << "buffer : " << info.buffer << std::endl;

    std::string out_file("raw_audio.pcm");

    save_audio_mp3_pcm(info.buffer, info.samples * sizeof(mp3d_sample_t), out_file);

    std::cout << "saved mp3 pcm file" << std::endl;
    return info;
}

void fingerprint_from_pcm(std::string &in_file, std::string &out_file, size_t frequency)
{

    short speech;

    if (!fs::exists("TEMP/" + in_file))
    {
        std::cout << "Could not locate file to fignerprint" << std::endl;
        exit(-1);
    }

    size_t size = fs::file_size("TEMP/" + in_file);
    float *num_data = new float[size / 2];

    std::ifstream f_in("TEMP/" + in_file, std::ios::in | std::ios::binary);
    int i = 0;
    while (f_in.good())
    {
        f_in.read((char *)&speech, 2);
        num_data[i] = speech;
        i++;
    }

    std::string json = fp::fingerprint(num_data, size / 2, frequency);

    delete[] num_data;
    std::ofstream json_prints;

    json_prints.open(out_file, std::ios::out);
    json_prints << json;
    json_prints.close();

    std::cout << "Fingerprints located in file :" << out_file << std::endl;
}

int main(int argc, char const *argv[])
{

    if (!argv[2])
    {

        std::cerr << "You must specify an input file and then an output file." << std::endl;
    }
    std::string in_path = argv[1];
    std::string out_path = argv[2];

    std::string extension(in_path.substr(in_path.length() - 4, in_path.length() - 1));
    std::cout << extension << std::endl;

    if (extension == ".mp3")
    {

        mp3dec_file_info_t mp3_infos = run_mp3_decoder();
        std::string mp3_in_f("raw_audio.pcm");

        fingerprint_from_pcm(mp3_in_f, out_path, mp3_infos.hz);
    }
    else if (extension == ".wav")
    {

        std::shared_ptr<wd::audio_data> wav_infos = run_wav_decoder();
        std::string wav_in_f("raw_audio.pcm");

        fingerprint_from_pcm(wav_in_f, out_path, wav_infos->sample_rate);
    }

    return 0;
}
