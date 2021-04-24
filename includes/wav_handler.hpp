#include <iostream>
#include <fstream>

#include <static_wav_decoder.hpp>
#include <globals.hpp>
#include <stdexcept>

namespace wd = wav_decoder;

std::string save_audio_wav_pcm(char *buffer, size_t length, std::string &file_name);

std::string run_wav_decoder(std::string source_path);
