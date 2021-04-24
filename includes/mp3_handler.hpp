#include <minimp3.h>

#include <iostream>
#include <fstream>


std::string save_audio_mp3_pcm(mp3d_sample_t *buffer, size_t length, std::string &file_name);

std::string run_mp3_decoder(std::string source_path);
