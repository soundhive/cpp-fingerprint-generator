#include <cstdlib>
#include <iostream>

#define BASE_DIR getenv( "TEMP_DIR" ) ? getenv( "TEMP_DIR" ) : "TEMP/"

namespace globals{
  std::string get_temp_base_dir();
}


