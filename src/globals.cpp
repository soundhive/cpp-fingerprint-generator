#include <globals.hpp>

std::string globals::get_temp_base_dir() {
  const auto res =  getenv( "TEMP_DIR" );
  if (!res) {
    return "TEMP/";
  }

  return std::string(res);
}

