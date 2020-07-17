#./libs/CMakeLists.txt

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dejavu_cpp_port")


set(DEPENDENCIES_HEADERS
"${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder/include"
"${CMAKE_CURRENT_SOURCE_DIR}/dejavu_cpp_port/include"

  PARENT_SCOPE
)


