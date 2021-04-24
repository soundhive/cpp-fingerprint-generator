//#define MINIMP3_FLOAT_OUTPUT
#define MINIMP3_IMPLEMENTATION
#include <minimp3_ex.h>

#include <mp3_handler.hpp>


std::string save_audio_mp3_pcm(mp3d_sample_t *buffer, size_t length, std::string &file_name)
{
  const std::string output_file = std::string(BASE_TEMP_DIR) + "/" + file_name;
  // Open output file
  std::ofstream out_stream(output_file, std::ofstream::binary);

  // Check that the output stream is valid
  if (!out_stream.good())
  {
    std::cerr << "Output stream to file "
              << output_file
              << " is not valid" << std::endl;
    throw std::system_error(EIO, std::generic_category(), "Could not save PCM out of mp3 file.");
  }

  out_stream.write(reinterpret_cast<char *>(buffer), length);

  out_stream.close();

  return output_file;
}

std::string run_mp3_decoder(std::string source_path)
{
  std::cout << "running mp3 decoder." << std::endl;

  mp3dec_t mp3d;
  mp3dec_file_info_t info;
  if (mp3dec_load(&mp3d, source_path.c_str(), &info, NULL, NULL))
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

  const std::string res = save_audio_mp3_pcm(info.buffer, info.samples * sizeof(mp3d_sample_t), out_file);

  std::cout << "saved mp3 pcm file" << std::endl;

  free(info.buffer);

  return res;
}
