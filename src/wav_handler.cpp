#include <wav_handler.hpp>


std::string run_wav_decoder(std::string source_path)
{
  std::cout << "running wav decoder." << std::endl;

  std::shared_ptr<wd::audio_data> data = wd::decode(source_path);

  std::cout << "format : " << data->audio_format << std::endl;
  std::cout << "channels : " << data->nb_channels << std::endl;
  std::cout << "byte rate : " << data->byte_rate << std::endl;
  std::cout << "sample rate : " << data->sample_rate << std::endl;
  std::cout << "block align : " << data->block_align << std::endl;
  std::cout << "bits per sample : " << data->bits_per_sample << std::endl;
  std::cout << "buffer length : " << data->buffer_length << std::endl;

  std::string out_file("raw_audio.pcm");

  return save_audio_wav_pcm(data->audio_buffer.get(), data->buffer_length, out_file);
}

std::string save_audio_wav_pcm(char *buffer, size_t length, std::string &file_name)
{
  const std::string output_file = std::string(BASE_TEMP_DIR) + "/" + file_name;
  // Open output file
  std::ofstream out_stream(output_file, std::ofstream::binary);

  // Check that the output stream is valid
  if (!out_stream.good())
  {
    std::cout << "Output stream to file "
              << "TEMP/" << file_name
              << " is not valid" << std::endl;
    throw std::system_error(EIO, std::generic_category(), "Could not save pcm out of wav file.");
  }

  out_stream.write(buffer, length);

  out_stream.close();

  std::cout << "Copy done" << std::endl;

  return output_file;
}